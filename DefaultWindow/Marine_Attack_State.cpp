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
		// 이동해야 할 방향 벡터 계산
		float dirX = target->Get_Info().fX - _marine->Get_Info().fX;
		float dirY = target->Get_Info().fY - _marine->Get_Info().fY;
		float length = sqrt(dirX * dirX + dirY * dirY);

		if (length < _marine->Get_Stat().m_AttackRange) { // 목표까지의 거리가 속도보다 클 경우, 이동 실행

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
			// 단위 방향 벡터와 속도를 사용하여 이동
			float speed = _marine->Get_Stat().m_fSpeed; // 적당한 속도 값
			dirX = (dirX / length) * speed;
			dirY = (dirY / length) * speed;
			_marine->Set_PosX(dirX);
			_marine->Set_PosY(dirY);
		}
	}
}
