#include "stdafx.h"
#include "Medic_Walk_State.h"

CMedic_Walk_State::CMedic_Walk_State()
{
}

CMedic_Walk_State::~CMedic_Walk_State()
{
}

void CMedic_Walk_State::Initialize(CObj_Dynamic* _medic)
{
	m_pFrameCopy = _medic->Get_Frame();
	m_pFrameKeyCopy = _medic->Get_FrameKey();

	*m_pFrameKeyCopy = L"Medic_Walk_Right_90";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 13;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 50;
	m_pFrameCopy->dwTime = GetTickCount();
	
}

int CMedic_Walk_State::Update(CObj_Dynamic*)
{
	return 0;
}

void CMedic_Walk_State::Late_Update(CObj_Dynamic*)
{
}

void CMedic_Walk_State::Render(CObj_Dynamic*, HDC hDC)
{
}

void CMedic_Walk_State::Release(CObj_Dynamic*)
{
}
