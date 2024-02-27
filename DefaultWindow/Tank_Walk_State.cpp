#include "stdafx.h"
#include "Tank_Walk_State.h"

CTank_Walk_State::CTank_Walk_State()
{
}

CTank_Walk_State::~CTank_Walk_State()
{
}

void CTank_Walk_State::Initialize(CObj_Dynamic* _tank)
{
	m_pFrameCopy = _tank->Get_Frame();
	m_pFrameKeyCopy = _tank->Get_FrameKey();

	*m_pFrameKeyCopy = L"Lower_Tank_Walk_Right_90";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 5;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 50;
	m_pFrameCopy->dwTime = GetTickCount();
}

int CTank_Walk_State::Update(CObj_Dynamic* _tank)
{
	if (Move(_tank) == MOVE_OK)
		_tank->ChangeState(IDLE_STATE);

    return 0;
}

void CTank_Walk_State::Late_Update(CObj_Dynamic*)
{
}

void CTank_Walk_State::Render(CObj_Dynamic*, HDC hDC)
{
}

void CTank_Walk_State::Release(CObj_Dynamic*)
{
}

void CTank_Walk_State::Move_Frame()
{
}
