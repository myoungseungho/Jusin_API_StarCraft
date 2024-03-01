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
	// ���� ��ǥ Ÿ���� ���ų� ��θ� ��� �Ϸ��� ���
	if (m_listPathTile.empty()) {
		return MOVE_OK; // �̵� ����
	}

	m_pFrameKeyCopy = _unit->Get_FrameKey();

	// ���� ��ǥ Ÿ��
	CObj* currentTargetTile = m_listPathTile.front();
	//dynamic_cast<CTile*>(currentTargetTile)->Set_Value(1, 0);

	// ���� ��ǥ Ÿ���� �߽� ��ǥ ���
	float targetX = currentTargetTile->Get_Info().fX;
	float targetY = currentTargetTile->Get_Info().fY;

	// SCV�� ���� ��ġ
	float unitX = _unit->Get_Info().fX;
	float unitY = _unit->Get_Info().fY;

	// �̵��ؾ� �� ���� ���� ���
	float dirX = targetX - unitX;
	float dirY = targetY - unitY;
	float radian = atan2(dirY, dirX);
	float degree = (radian * 180) / PI;
	float length = sqrt(dirX * dirX + dirY * dirY);

	// ���� ���� ���Ϳ� �ӵ��� ����Ͽ� �̵�
	float speed = _unit->Get_Stat().m_fSpeed; // ������ �ӵ� ��
	if (length > speed) { // ��ǥ������ �Ÿ��� �ӵ����� Ŭ ���, �̵� ����
		dirX = (dirX / length) * speed;
		dirY = (dirY / length) * speed;
		_unit->Set_PosX(dirX);
		_unit->Set_PosY(dirY);

		DetermineKey(_unit, degree);
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

void IState::DetermineKey(CObj_Dynamic* _unit, float degree)
{
	if (_unit->GetStateID() == WALK_STATE)
	{
		if (degree > -22.5f && degree <= 22.5f) {
			//����
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_RIGHT];
		}
		else if (degree > 22.5f && degree <= 67.5f) {
			// ������
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_RDOWN];
		}
		else if (degree > 67.5f && degree <= 112.5f) {
			// ����
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_DOWN];
		}
		else if (degree > 112.5f && degree <= 157.5f) {
			// ������
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_LDOWN];
		}
		else if ((degree > 157.5f && degree <= 180.f) || (degree <= -157.5f && degree >= -180.f)) {
			// ����
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_LEFT];
		}
		else if (degree > -157.5f && degree <= -112.5f) {
			// �ϼ���
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_LUP];
		}
		else if (degree > -112.5f && degree <= -67.5f) {
			// ����
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_UP];
		}
		else if (degree > -67.5f && degree <= -22.5f) {
			// �ϵ���
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_RUP];
		}

	}
	else if (_unit->GetStateID() == ATTACK_STATE)
	{
		if (degree > -22.5f && degree <= 22.5f) {
			//����
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayAttackKey[DIR_RIGHT];
		}
		else if (degree > 22.5f && degree <= 67.5f) {
			// ������
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayAttackKey[DIR_RDOWN];
		}
		else if (degree > 67.5f && degree <= 112.5f) {
			// ����
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayAttackKey[DIR_DOWN];
		}
		else if (degree > 112.5f && degree <= 157.5f) {
			// ������
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayAttackKey[DIR_LDOWN];
		}
		else if ((degree > 157.5f && degree <= 180.f) || (degree <= -157.5f && degree >= -180.f)) {
			// ����
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayAttackKey[DIR_LEFT];
		}
		else if (degree > -157.5f && degree <= -112.5f) {
			// �ϼ���
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayAttackKey[DIR_LUP];
		}
		else if (degree > -112.5f && degree <= -67.5f) {
			// ����
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayAttackKey[DIR_UP];
		}
		else if (degree > -67.5f && degree <= -22.5f) {
			// �ϵ���
			*m_pFrameKeyCopy = _unit->GetKeyAndFrame()->m_FrameArrayAttackKey[DIR_RUP];
		}

		if (_unit->GetType() == DYNAMIC_OBJ_FIREBAT)
		{
			if (degree > -22.5f && degree <= 22.5f) {
				//����
				m_pFrameKey_Attack = _unit->GetKeyAndFrame()->m_FrameBulletAttackKey[DIR_RIGHT];
			}
			else if (degree > 22.5f && degree <= 67.5f) {
				// ������
				m_pFrameKey_Attack = _unit->GetKeyAndFrame()->m_FrameBulletAttackKey[DIR_RDOWN];
			}
			else if (degree > 67.5f && degree <= 112.5f) {
				// ����
				m_pFrameKey_Attack = _unit->GetKeyAndFrame()->m_FrameBulletAttackKey[DIR_DOWN];
			}
			else if (degree > 112.5f && degree <= 157.5f) {
				// ������
				m_pFrameKey_Attack = _unit->GetKeyAndFrame()->m_FrameBulletAttackKey[DIR_LDOWN];
			}
			else if ((degree > 157.5f && degree <= 180.f) || (degree <= -157.5f && degree >= -180.f)) {
				// ����
				m_pFrameKey_Attack = _unit->GetKeyAndFrame()->m_FrameBulletAttackKey[DIR_LEFT];
			}
			else if (degree > -157.5f && degree <= -112.5f) {
				// �ϼ���
				m_pFrameKey_Attack = _unit->GetKeyAndFrame()->m_FrameBulletAttackKey[DIR_LUP];
			}
			else if (degree > -112.5f && degree <= -67.5f) {
				// ����
				m_pFrameKey_Attack = _unit->GetKeyAndFrame()->m_FrameBulletAttackKey[DIR_UP];
			}
			else if (degree > -67.5f && degree <= -22.5f) {
				// �ϵ���
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
			//����
			m_pFrameKey_TankPosin = _unit->GetKeyAndFrame()->m_FrameTankPosinKey[DIR_RIGHT];
		}
		else if (degree > 22.5f && degree <= 67.5f) {
			// ������
			m_pFrameKey_TankPosin = _unit->GetKeyAndFrame()->m_FrameTankPosinKey[DIR_RDOWN];
		}
		else if (degree > 67.5f && degree <= 112.5f) {
			// ����
			m_pFrameKey_TankPosin = _unit->GetKeyAndFrame()->m_FrameTankPosinKey[DIR_DOWN];
		}
		else if (degree > 112.5f && degree <= 157.5f) {
			// ������
			m_pFrameKey_TankPosin = _unit->GetKeyAndFrame()->m_FrameTankPosinKey[DIR_LDOWN];
		}
		else if ((degree > 157.5f && degree <= 180.f) || (degree <= -157.5f && degree >= -180.f)) {
			// ����
			m_pFrameKey_TankPosin = _unit->GetKeyAndFrame()->m_FrameTankPosinKey[DIR_LEFT];
		}
		else if (degree > -157.5f && degree <= -112.5f) {
			// �ϼ���
			m_pFrameKey_TankPosin = _unit->GetKeyAndFrame()->m_FrameTankPosinKey[DIR_LUP];
		}
		else if (degree > -112.5f && degree <= -67.5f) {
			// ����
			m_pFrameKey_TankPosin = _unit->GetKeyAndFrame()->m_FrameTankPosinKey[DIR_UP];
		}
		else if (degree > -67.5f && degree <= -22.5f) {
			// �ϵ���
			m_pFrameKey_TankPosin = _unit->GetKeyAndFrame()->m_FrameTankPosinKey[DIR_RUP];
		}
	}

	m_pFrameCopy->iFrameStart = _unit->GetKeyAndFrame()->_mapKeyFrame[*m_pFrameKeyCopy].iFrameStart;
	m_pFrameCopy->iFrameEnd = _unit->GetKeyAndFrame()->_mapKeyFrame[*m_pFrameKeyCopy].iFrameEnd;
	m_pFrameCopy->iMotion = _unit->GetKeyAndFrame()->_mapKeyFrame[*m_pFrameKeyCopy].iMotion;
	m_pFrameCopy->dwSpeed = _unit->GetKeyAndFrame()->_mapKeyFrame[*m_pFrameKeyCopy].dwSpeed;
	m_pFrameCopy->dwTime = _unit->GetKeyAndFrame()->_mapKeyFrame[*m_pFrameKeyCopy].dwTime;
}