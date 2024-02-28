#include "stdafx.h"
#include "Tank_Attack_State.h"

CTank_Attack_State::CTank_Attack_State()
{
}

CTank_Attack_State::~CTank_Attack_State()
{
}

void CTank_Attack_State::Initialize(CObj_Dynamic* _tank)
{
	m_pFrameCopy = _tank->Get_Frame();
	m_pFrameKeyCopy = _tank->Get_FrameKey();

	*m_pFrameKeyCopy = L"Lower_Tank_Walk_Right_90";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 5;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 50;
	m_pFrameCopy->dwTime = GetTickCount();

	m_bAttackDistanceIn = false;
}

int CTank_Attack_State::Update(CObj_Dynamic* _tank)
{
	if (!_tank->CheckEnemy())
	{
		_tank->ChangeState(IDLE_STATE);
	}
	else
	{
		if (!m_bAttackDistanceIn)
			MoveUntilAttackDistance(_tank);
	}

	return 0;
}

void CTank_Attack_State::Late_Update(CObj_Dynamic*)
{
}

void CTank_Attack_State::Render(CObj_Dynamic*, HDC hDC)
{
}

void CTank_Attack_State::Release(CObj_Dynamic*)
{
}

void CTank_Attack_State::Move_Frame()
{
}

void CTank_Attack_State::MoveUntilAttackDistance(CObj_Dynamic* _tank)
{
	CObj* target = _tank->Get_Target();
	if (target != nullptr)
	{
		// 이동해야 할 방향 벡터 계산
		float dirX = target->Get_Info().fX - _tank->Get_Info().fX;
		float dirY = target->Get_Info().fY - _tank->Get_Info().fY;
		float length = sqrt(dirX * dirX + dirY * dirY);

		if (length < _tank->Get_Stat().m_AttackRange) { // 목표까지의 거리가 속도보다 클 경우, 이동 실행

			m_bAttackDistanceIn = true;

			m_pFrameCopy = _tank->Get_Frame();
			m_pFrameKeyCopy = _tank->Get_FrameKey();

			*m_pFrameKeyCopy = L"Lower_Tank_Walk_Right_90";
			m_pFrameCopy->iFrameStart = 0;
			m_pFrameCopy->iFrameEnd = 5;
			m_pFrameCopy->iMotion = 0;
			m_pFrameCopy->dwSpeed = 50;
			m_pFrameCopy->dwTime = GetTickCount();
		}
		else
		{
			// 단위 방향 벡터와 속도를 사용하여 이동
			float speed = _tank->Get_Stat().m_fSpeed; // 적당한 속도 값
			dirX = (dirX / length) * speed;
			dirY = (dirY / length) * speed;
			_tank->Set_PosX(dirX);
			_tank->Set_PosY(dirY);
		}
	}
}
