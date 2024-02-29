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

	_tank->SetAttackRun(false);
}

int CTank_Attack_State::Update(CObj_Dynamic* _tank)
{
	if (!_tank->CheckEnemy())
	{
		_tank->ChangeState(IDLE_STATE);
	}
	else
	{
		if (!_tank->GetAttackRun())
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

void CTank_Attack_State::Move_Frame(CObj_Dynamic*)
{
}

