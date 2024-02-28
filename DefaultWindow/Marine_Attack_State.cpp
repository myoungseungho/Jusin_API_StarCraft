#include "stdafx.h"
#include "Marine_Attack_State.h"

CMarine_Attack_State::CMarine_Attack_State()
{
}

CMarine_Attack_State::~CMarine_Attack_State()
{
}

void CMarine_Attack_State::Initialize(CObj_Dynamic* _marine)
{
	m_pFrameCopy = _marine->Get_Frame();
	m_pFrameKeyCopy = _marine->Get_FrameKey();

	*m_pFrameKeyCopy = L"Marine_Walk_Right_90";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 17;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 50;
	m_pFrameCopy->dwTime = GetTickCount();

	m_bAttackDistanceIn = false;
}

int CMarine_Attack_State::Update(CObj_Dynamic* _marine)
{
	if (!_marine->CheckEnemy())
	{
		_marine->ChangeState(IDLE_STATE);
	}
	else
	{
		if (!m_bAttackDistanceIn)
			MoveUntilAttackDistance(_marine);
	}

	return 0;
}

void CMarine_Attack_State::Late_Update(CObj_Dynamic*)
{
}

void CMarine_Attack_State::Render(CObj_Dynamic*, HDC hDC)
{
}

void CMarine_Attack_State::Release(CObj_Dynamic*)
{
}

void CMarine_Attack_State::Move_Frame()
{
}

void CMarine_Attack_State::MoveUntilAttackDistance(CObj_Dynamic* _marine)
{
	CObj* target = _marine->Get_Target();
	if (target != nullptr)
	{
		// �̵��ؾ� �� ���� ���� ���
		float dirX = target->Get_Info().fX - _marine->Get_Info().fX;
		float dirY = target->Get_Info().fY - _marine->Get_Info().fY;
		float length = sqrt(dirX * dirX + dirY * dirY);

		if (length < _marine->Get_Stat().m_AttackRange) { // ��ǥ������ �Ÿ��� �ӵ����� Ŭ ���, �̵� ����

			m_bAttackDistanceIn = true;

			m_pFrameCopy = _marine->Get_Frame();
			m_pFrameKeyCopy = _marine->Get_FrameKey();

			*m_pFrameKeyCopy = L"Mairen_Attack_Right_90";
			m_pFrameCopy->iFrameStart = 0;
			m_pFrameCopy->iFrameEnd = 5;
			m_pFrameCopy->iMotion = 0;
			m_pFrameCopy->dwSpeed = 100;
			m_pFrameCopy->dwTime = GetTickCount();
		}
		else
		{
			// ���� ���� ���Ϳ� �ӵ��� ����Ͽ� �̵�
			float speed = _marine->Get_Stat().m_fSpeed; // ������ �ӵ� ��
			dirX = (dirX / length) * speed;
			dirY = (dirY / length) * speed;
			_marine->Set_PosX(dirX);
			_marine->Set_PosY(dirY);
		}
	}
}
