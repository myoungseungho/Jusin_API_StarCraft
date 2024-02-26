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
	// ���� ��ǥ Ÿ���� ���ų� ��θ� ��� �Ϸ��� ���
	if (m_listPathTile.empty()) {
		return; // �̵� ����
	}

	// ���� ��ǥ Ÿ��
	CObj* currentTargetTile = m_listPathTile.front();
	dynamic_cast<CTile*>(currentTargetTile)->Set_Value(1, 0);

	// ���� ��ǥ Ÿ���� �߽� ��ǥ ���
	float targetX = currentTargetTile->Get_Info().fX;
	float targetY = currentTargetTile->Get_Info().fY;

	// SCV�� ���� ��ġ
	float unitX = _unit->Get_Info().fX;
	float unitY = _unit->Get_Info().fY;

	// �̵��ؾ� �� ���� ���� ���
	float dirX = targetX - unitX;
	float dirY = targetY - unitY;
	float length = sqrt(dirX * dirX + dirY * dirY);

	// ���� ���� ���Ϳ� �ӵ��� ����Ͽ� �̵�
	float speed = 5.0f; // ������ �ӵ� ��
	if (length > speed) { // ��ǥ������ �Ÿ��� �ӵ����� Ŭ ���, �̵� ����
		dirX = (dirX / length) * speed;
		dirY = (dirY / length) * speed;
		_unit->Set_PosX(dirX);
		_unit->Set_PosY(dirY);
	}
	else {
		// ��ǥ Ÿ�Ͽ� �����߰ų� �ſ� ����� ���, ��ǥ Ÿ���� ���� Ÿ�Ϸ� ����
		m_listPathTile.pop_front();
		if (!m_listPathTile.empty()) {
			// ���� Ÿ�Ϸ� �̵��� ����մϴ�.
			Move(_unit);
		}
	}
}