#include "stdafx.h"
#include "State.h"
#include "AStarMgr.h"
#include "Tile.h"
IState::IState()
{
}

IState::~IState()
{
}

void IState::Move_Frame()
{
}

void IState::Set_Astar(float _fX, float _fY, float _goalX, float _goalY)
{
	pair<int, int> start(_fX, _fY);
	pair<int, int> goal(_goalX, _goalY);

	m_Path = CAStarMgr::Get_Instance()->AStarSearch(start, goal);
}

void IState::Move(CObj_Dynamic* _unit)
{
	// 현재 목표 타일이 없거나 경로를 모두 완료한 경우
	if (m_listPathTile.empty()) {
		return; // 이동 중지
	}

	// 현재 목표 타일
	CObj* currentTargetTile = m_listPathTile.front();
	dynamic_cast<CTile*>(currentTargetTile)->Set_Value(1, 0);

	// 현재 목표 타일의 중심 좌표 계산
	float targetX = currentTargetTile->Get_Info().fX;
	float targetY = currentTargetTile->Get_Info().fY;

	// SCV의 현재 위치
	float unitX = _unit->Get_Info().fX;
	float unitY = _unit->Get_Info().fY;

	// 이동해야 할 방향 벡터 계산
	float dirX = targetX - unitX;
	float dirY = targetY - unitY;
	float length = sqrt(dirX * dirX + dirY * dirY);

	// 단위 방향 벡터와 속도를 사용하여 이동
	float speed = 5.0f; // 적당한 속도 값
	if (length > speed) { // 목표까지의 거리가 속도보다 클 경우, 이동 실행
		dirX = (dirX / length) * speed;
		dirY = (dirY / length) * speed;
		_unit->Set_PosX(dirX);
		_unit->Set_PosY(dirY);
	}
	else {
		// 목표 타일에 도달했거나 매우 가까운 경우, 목표 타일을 다음 타일로 변경
		m_listPathTile.pop_front();
		if (!m_listPathTile.empty()) {
			// 다음 타일로 이동을 계속합니다.
			Move(_unit);
		}
	}
}