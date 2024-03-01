#include "stdafx.h"
#include "State.h"
#include "AStarMgr.h"
#include "Tile.h"
IState::IState() : m_dwTime(GetTickCount())
{
}

IState::~IState()
{
}


void IState::Set_Astar(float _fX, float _fY, float _goalX, float _goalY)
{
	pair<int, int> start(_fX, _fY);
	pair<int, int> goal(_goalX, _goalY);

	m_Path = CAStarMgr::Get_Instance()->AStarSearch(start, goal);
}

int IState::Move(CObj_Dynamic* _unit)
{
	// 현재 목표 타일이 없거나 경로를 모두 완료한 경우
	if (m_listPathTile.empty()) {
		return MOVE_OK; // 이동 중지
	}

	m_pFrameKeyCopy = _unit->Get_FrameKey();

	// 현재 목표 타일
	CObj* currentTargetTile = m_listPathTile.front();
	//dynamic_cast<CTile*>(currentTargetTile)->Set_Value(1, 0);

	// 현재 목표 타일의 중심 좌표 계산
	float targetX = currentTargetTile->Get_Info().fX;
	float targetY = currentTargetTile->Get_Info().fY;

	// SCV의 현재 위치
	float unitX = _unit->Get_Info().fX;
	float unitY = _unit->Get_Info().fY;

	// 이동해야 할 방향 벡터 계산
	float dirX = targetX - unitX;
	float dirY = targetY - unitY;
	float radian = atan2(dirY, dirX);
	float degree = (radian * 180) / PI;
	float length = sqrt(dirX * dirX + dirY * dirY);

	// 단위 방향 벡터와 속도를 사용하여 이동
	float speed = _unit->Get_Stat().m_fSpeed; // 적당한 속도 값
	if (length > speed) { // 목표까지의 거리가 속도보다 클 경우, 이동 실행
		dirX = (dirX / length) * speed;
		dirY = (dirY / length) * speed;
		_unit->Set_PosX(dirX);
		_unit->Set_PosY(dirY);

		DetermineKey(_unit, degree);
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

void IState::DetermineKey(CObj_Dynamic* _unit, float degree)
{
	if (_unit->GetStateID() == WALK_STATE)
	{
		if (degree > -22.5f && degree <= 22.5f) {
			//동쪽
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_RIGHT];
		}
		else if (degree > 22.5f && degree <= 67.5f) {
			// 남동쪽
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_RDOWN];
		}
		else if (degree > 67.5f && degree <= 112.5f) {
			// 남쪽
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_DOWN];
		}
		else if (degree > 112.5f && degree <= 157.5f) {
			// 남서쪽
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_LDOWN];
		}
		else if ((degree > 157.5f && degree <= 180.f) || (degree <= -157.5f && degree >= -180.f)) {
			// 서쪽
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_LEFT];
		}
		else if (degree > -157.5f && degree <= -112.5f) {
			// 북서쪽
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_LUP];
		}
		else if (degree > -112.5f && degree <= -67.5f) {
			// 북쪽
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_UP];
		}
		else if (degree > -67.5f && degree <= -22.5f) {
			// 북동쪽
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_RUP];
		}

	}
	else if (_unit->GetStateID() == ATTACK_STATE)
	{
		if (degree > -22.5f && degree <= 22.5f) {
			//동쪽
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayAttackKey[DIR_RIGHT];
		}
		else if (degree > 22.5f && degree <= 67.5f) {
			// 남동쪽
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayAttackKey[DIR_RDOWN];
		}
		else if (degree > 67.5f && degree <= 112.5f) {
			// 남쪽
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayAttackKey[DIR_DOWN];
		}
		else if (degree > 112.5f && degree <= 157.5f) {
			// 남서쪽
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayAttackKey[DIR_LDOWN];
		}
		else if ((degree > 157.5f && degree <= 180.f) || (degree <= -157.5f && degree >= -180.f)) {
			// 서쪽
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayAttackKey[DIR_LEFT];
		}
		else if (degree > -157.5f && degree <= -112.5f) {
			// 북서쪽
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayAttackKey[DIR_LUP];
		}
		else if (degree > -112.5f && degree <= -67.5f) {
			// 북쪽
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayAttackKey[DIR_UP];
		}
		else if (degree > -67.5f && degree <= -22.5f) {
			// 북동쪽
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayAttackKey[DIR_RUP];
		}

		if (_unit->GetType() == DYNAMIC_OBJ_FIREBAT)
		{
			if (degree > -22.5f && degree <= 22.5f) {
				//동쪽
				m_pFrameKey_Attack = _unit->GetKeyAndFrame()->m_FrameBulletAttackKey[DIR_RIGHT];
			}
			else if (degree > 22.5f && degree <= 67.5f) {
				// 남동쪽
				m_pFrameKey_Attack = _unit->GetKeyAndFrame()->m_FrameBulletAttackKey[DIR_RDOWN];
			}
			else if (degree > 67.5f && degree <= 112.5f) {
				// 남쪽
				m_pFrameKey_Attack = _unit->GetKeyAndFrame()->m_FrameBulletAttackKey[DIR_DOWN];
			}
			else if (degree > 112.5f && degree <= 157.5f) {
				// 남서쪽
				m_pFrameKey_Attack = _unit->GetKeyAndFrame()->m_FrameBulletAttackKey[DIR_LDOWN];
			}
			else if ((degree > 157.5f && degree <= 180.f) || (degree <= -157.5f && degree >= -180.f)) {
				// 서쪽
				m_pFrameKey_Attack = _unit->GetKeyAndFrame()->m_FrameBulletAttackKey[DIR_LEFT];
			}
			else if (degree > -157.5f && degree <= -112.5f) {
				// 북서쪽
				m_pFrameKey_Attack = _unit->GetKeyAndFrame()->m_FrameBulletAttackKey[DIR_LUP];
			}
			else if (degree > -112.5f && degree <= -67.5f) {
				// 북쪽
				m_pFrameKey_Attack = _unit->GetKeyAndFrame()->m_FrameBulletAttackKey[DIR_UP];
			}
			else if (degree > -67.5f && degree <= -22.5f) {
				// 북동쪽
				m_pFrameKey_Attack = _unit->GetKeyAndFrame()->m_FrameBulletAttackKey[DIR_RUP];
			}

			m_tFrame_Attack.iFrameStart = _unit->GetKeyAndFrame()->_mapKeyFrame[m_pFrameKey_Attack].iFrameStart;
			m_tFrame_Attack.iFrameEnd = _unit->GetKeyAndFrame()->_mapKeyFrame[m_pFrameKey_Attack].iFrameEnd;
			m_tFrame_Attack.iMotion = _unit->GetKeyAndFrame()->_mapKeyFrame[m_pFrameKey_Attack].iMotion;
			m_tFrame_Attack.dwSpeed = _unit->GetKeyAndFrame()->_mapKeyFrame[m_pFrameKey_Attack].dwSpeed;
			m_tFrame_Attack.dwTime = _unit->GetKeyAndFrame()->_mapKeyFrame[m_pFrameKey_Attack].dwTime;
		}
	}

	if (_unit->GetType() == DYNAMIC_OBJ_TANK)
	{
		if (degree > -22.5f && degree <= 22.5f) {
			//동쪽
			m_pFrameKey_TankPosin = _unit->GetKeyAndFrame()->m_FrameTankPosinKey[DIR_RIGHT];
		}
		else if (degree > 22.5f && degree <= 67.5f) {
			// 남동쪽
			m_pFrameKey_TankPosin = _unit->GetKeyAndFrame()->m_FrameTankPosinKey[DIR_RDOWN];
		}
		else if (degree > 67.5f && degree <= 112.5f) {
			// 남쪽
			m_pFrameKey_TankPosin = _unit->GetKeyAndFrame()->m_FrameTankPosinKey[DIR_DOWN];
		}
		else if (degree > 112.5f && degree <= 157.5f) {
			// 남서쪽
			m_pFrameKey_TankPosin = _unit->GetKeyAndFrame()->m_FrameTankPosinKey[DIR_LDOWN];
		}
		else if ((degree > 157.5f && degree <= 180.f) || (degree <= -157.5f && degree >= -180.f)) {
			// 서쪽
			m_pFrameKey_TankPosin = _unit->GetKeyAndFrame()->m_FrameTankPosinKey[DIR_LEFT];
		}
		else if (degree > -157.5f && degree <= -112.5f) {
			// 북서쪽
			m_pFrameKey_TankPosin = _unit->GetKeyAndFrame()->m_FrameTankPosinKey[DIR_LUP];
		}
		else if (degree > -112.5f && degree <= -67.5f) {
			// 북쪽
			m_pFrameKey_TankPosin = _unit->GetKeyAndFrame()->m_FrameTankPosinKey[DIR_UP];
		}
		else if (degree > -67.5f && degree <= -22.5f) {
			// 북동쪽
			m_pFrameKey_TankPosin = _unit->GetKeyAndFrame()->m_FrameTankPosinKey[DIR_RUP];
		}
	}

	m_pFrameCopy->iFrameStart = _unit->GetKeyAndFrame()->_mapKeyFrame[*m_pFrameKeyCopy].iFrameStart;
	m_pFrameCopy->iFrameEnd = _unit->GetKeyAndFrame()->_mapKeyFrame[*m_pFrameKeyCopy].iFrameEnd;
	m_pFrameCopy->iMotion = _unit->GetKeyAndFrame()->_mapKeyFrame[*m_pFrameKeyCopy].iMotion;
	m_pFrameCopy->dwSpeed = _unit->GetKeyAndFrame()->_mapKeyFrame[*m_pFrameKeyCopy].dwSpeed;
	m_pFrameCopy->dwTime = _unit->GetKeyAndFrame()->_mapKeyFrame[*m_pFrameKeyCopy].dwTime;
}