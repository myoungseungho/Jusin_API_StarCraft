#include "stdafx.h"
#include "Ghost_Idle_State.h"

CGhost_Idle_State::CGhost_Idle_State()
{
}

CGhost_Idle_State::~CGhost_Idle_State()
{
}

void CGhost_Idle_State::Initialize(CObj_Dynamic* _ghost)
{
	m_pFrameCopy = _ghost->Get_Frame();
	m_pFrameKeyCopy = _ghost->Get_FrameKey();

	*m_pFrameKeyCopy = L"Ghost_Idle";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 0;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 200;
	m_pFrameCopy->dwTime = GetTickCount();


	if (_ghost->Get_Stat().m_Hp < 0)
		_ghost->ChangeState(DIE_STATE);
}

int CGhost_Idle_State::Update(CObj_Dynamic*)
{
	return 0;
}

void CGhost_Idle_State::Late_Update(CObj_Dynamic*)
{
}

void CGhost_Idle_State::Render(CObj_Dynamic*, HDC hDC)
{
}

void CGhost_Idle_State::Release(CObj_Dynamic*)
{
}

void CGhost_Idle_State::Move_Frame(CObj_Dynamic*)
{
}
