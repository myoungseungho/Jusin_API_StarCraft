#include "stdafx.h"
#include "AttackState.h"
#include "SoundMgr.h"
IAttackState::IAttackState() : m_currentTime(GetTickCount())
{
}

IAttackState::~IAttackState()
{
}

void IAttackState::Initialize(CObj_Dynamic*)
{
}

int IAttackState::Update(CObj_Dynamic*)
{
	return 0;
}

void IAttackState::Late_Update(CObj_Dynamic*)
{
}

void IAttackState::Render(CObj_Dynamic*, HDC hDC)
{
}

void IAttackState::Release(CObj_Dynamic*)
{
}

void IAttackState::Move_Frame(CObj_Dynamic*)
{
}

void IAttackState::Attack(CObj_Dynamic* _unit)
{
	CObj* target = _unit->Get_Target();
	//�̹� ���� Ÿ������ �ϴ� �ٸ� ������ ���� ���¿���, target->
	if (target == nullptr || target->Get_Dead())
	{
		_unit->SetAttackRun(false);
		_unit->ChangeState(IDLE_STATE);
		_unit->Set_Clear_Target();
		return;
	}

	// �̵��ؾ� �� ���� ���� ���
	float dirX = target->Get_Info().fX - _unit->Get_Info().fX;
	float dirY = target->Get_Info().fY - _unit->Get_Info().fY;
	float radian = atan2(dirY, dirX);
	float degree = (radian * 180) / PI;

	//���̾���� ������ ���ݾִϸ��̼� �ӵ��� ���缭.
	if (_unit->GetType() == DYNAMIC_OBJ_FIREBAT)
	{
		if (m_tFrame_Attack.iFrameStart == 0)
		{
			if (target != nullptr && !target->Get_Dead())
			{
				CObj_Dynamic* dynamicObj = dynamic_cast<CObj_Dynamic*>(target);
				if (dynamicObj != nullptr)
				{
					vector<wchar_t*> m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound(DYNAMIC_OBJ_FIREBAT, SOUND_ATTACK);
					CSoundMgr::Get_Instance()->PlaySound(m_UnitSound.back(), SOUND_FIREBAT_ATTACK, 1);

					DetermineKey(_unit, degree);
					dynamic_cast<CObj_Dynamic*>(target)->Set_Damage(_unit->Get_Stat().m_Attack);
				}
			}
		}
	}
	else if (_unit->GetType() == DYNAMIC_OBJ_TANK)
	{
		if (m_currentTime + 2000 < GetTickCount())
		{
			m_currentTime = GetTickCount();
			if (target != nullptr && !target->Get_Dead())
			{
				CObj_Dynamic* dynamicObj = dynamic_cast<CObj_Dynamic*>(target);
				if (dynamicObj != nullptr)
				{
					vector<wchar_t*> m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound(DYNAMIC_OBJ_TANK, SOUND_ATTACK);
					CSoundMgr::Get_Instance()->PlaySound(m_UnitSound.back(), SOUND_TANK_ATTACK, 1);
					DetermineKey(_unit, degree);
					dynamic_cast<CObj_Dynamic*>(target)->Set_Damage(_unit->Get_Stat().m_Attack);
				}
			}
		}
	}
	else if (_unit->GetType() == DYNAMIC_OBJ_MEDIC)
	{
		if (_unit->Get_Frame()->iFrameStart == 0)
		{
			if (target != nullptr && !target->Get_Dead())
			{
				CObj_Dynamic* dynamicObj = dynamic_cast<CObj_Dynamic*>(target);
				if (dynamicObj != nullptr)
				{
					if (target->Get_Stat().m_Hp == target->Get_Stat().m_MaxHp )
						_unit->ChangeState(IDLE_STATE);

					DetermineKey(_unit, degree);
					dynamic_cast<CObj_Dynamic*>(target)->Set_Damage(_unit->Get_Stat().m_Attack);
				}
			}
		}
	}
	else
	{
		if (_unit->Get_Frame()->iFrameStart == 0)
		{
			if (target != nullptr && !target->Get_Dead())
			{
				CObj_Dynamic* dynamicObj = dynamic_cast<CObj_Dynamic*>(target);
				if (dynamicObj != nullptr)
				{
					if (dynamicObj->GetType() == DYNAMIC_OBJ_MARINE)
					{
						vector<wchar_t*> m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound(DYNAMIC_OBJ_MARINE, SOUND_ATTACK);
						CSoundMgr::Get_Instance()->PlaySound(m_UnitSound.back(), SOUND_MARINE_ATTACK, 1);
					}

					DetermineKey(_unit, degree);
					dynamic_cast<CObj_Dynamic*>(target)->Set_Damage(_unit->Get_Stat().m_Attack);
				}
			}
		}
	}
}


void IAttackState::MoveUntilAttackDistance(CObj_Dynamic* _unit)
{
	CObj* target = _unit->Get_Target();
	if (target == nullptr || target->Get_Dead())
		_unit->ChangeState(IDLE_STATE);

	// �̵��ؾ� �� ���� ���� ���
	float dirX = target->Get_Info().fX - _unit->Get_Info().fX;
	float dirY = target->Get_Info().fY - _unit->Get_Info().fY;
	float radian = atan2(dirY, dirX);
	float degree = (radian * 180) / PI;

	float length = sqrt(dirX * dirX + dirY * dirY);

	if (length < _unit->Get_Stat().m_AttackRange) { // ��ǥ������ �Ÿ��� �ӵ����� Ŭ ���, �̵� ����

		_unit->SetAttackRun(true);
		DetermineKey(_unit, degree);
	}
	else
	{
		// ���� ���� ���Ϳ� �ӵ��� ����Ͽ� �̵�
		float speed = _unit->Get_Stat().m_fSpeed; // ������ �ӵ� ��
		dirX = (dirX / length) * speed;
		dirY = (dirY / length) * speed;
		_unit->Set_PosX(dirX);
		_unit->Set_PosY(dirY);
	}
}
