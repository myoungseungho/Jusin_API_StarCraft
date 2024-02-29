#include "stdafx.h"
#include "AttackState.h"

IAttackState::IAttackState()
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
