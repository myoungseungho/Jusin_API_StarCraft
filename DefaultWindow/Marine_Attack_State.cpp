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

	*m_pFrameKeyCopy = L"Mairen_Attack_Right_90";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 5;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 100;
	m_pFrameCopy->dwTime = GetTickCount();
}

int CMarine_Attack_State::Update(CObj_Dynamic*)
{
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
