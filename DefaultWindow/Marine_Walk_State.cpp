#include "stdafx.h"
#include "Marine_Walk_State.h"

CMarine_Walk_State::CMarine_Walk_State()
{
}

CMarine_Walk_State::~CMarine_Walk_State()
{
}

void CMarine_Walk_State::Initialize(CObj_Dynamic* _marine)
{
	m_pFrameCopy = _marine->Get_Frame();
	m_pFrameKeyCopy = _marine->Get_FrameKey();

	*m_pFrameKeyCopy = L"Marine_Walk_Right_90";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 17;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 50;
	m_pFrameCopy->dwTime = GetTickCount();
}

int CMarine_Walk_State::Update(CObj_Dynamic*)
{
	return 0;
}

void CMarine_Walk_State::Late_Update(CObj_Dynamic*)
{
}

void CMarine_Walk_State::Render(CObj_Dynamic*, HDC hDC)
{
}

void CMarine_Walk_State::Release(CObj_Dynamic*)
{
}

void CMarine_Walk_State::Move_Frame()
{
}
