#include "stdafx.h"
#include "Tank_Idle_State.h"

CTank_Idle_State::CTank_Idle_State()
{
}

CTank_Idle_State::~CTank_Idle_State()
{
}

void CTank_Idle_State::Initialize(CObj_Dynamic* _tank)
{
	m_pFrameCopy = _tank->Get_Frame();
	m_pFrameKeyCopy = _tank->Get_FrameKey();

	*m_pFrameKeyCopy = L"Lower_Tank_Walk_Right_90";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 5;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 100;
	m_pFrameCopy->dwTime = GetTickCount();
}

int CTank_Idle_State::Update(CObj_Dynamic* _tank)
{
	if (m_dwTime + 1000 < GetTickCount())
	{
		_tank->CheckEnemy();
		m_dwTime = GetTickCount();
	}
	return 0;
}

void CTank_Idle_State::Late_Update(CObj_Dynamic*)
{
}

void CTank_Idle_State::Render(CObj_Dynamic*, HDC hDC)
{
}

void CTank_Idle_State::Release(CObj_Dynamic*)
{
}

void CTank_Idle_State::Move_Frame(CObj_Dynamic*)
{
}
