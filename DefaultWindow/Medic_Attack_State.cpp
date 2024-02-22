#include "stdafx.h"
#include "Medic_Attack_State.h"

CMedic_Attack_State::CMedic_Attack_State()
{
}

CMedic_Attack_State::~CMedic_Attack_State()
{
}

void CMedic_Attack_State::Initialize(CObj_Dynamic* _medic)
{
	m_pFrameCopy = _medic->Get_Frame();
	m_pFrameKeyCopy = _medic->Get_FrameKey();

	*m_pFrameKeyCopy = L"Medic_Attack_Right";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 3;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 100;
	m_pFrameCopy->dwTime = GetTickCount();
}

int CMedic_Attack_State::Update(CObj_Dynamic*)
{
	return 0;
}

void CMedic_Attack_State::Late_Update(CObj_Dynamic*)
{
}

void CMedic_Attack_State::Render(CObj_Dynamic*, HDC hDC)
{
}

void CMedic_Attack_State::Release(CObj_Dynamic*)
{
}

void CMedic_Attack_State::Move_Frame()
{
}
