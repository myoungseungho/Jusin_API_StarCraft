#include "stdafx.h"
#include "Medic_Idle_State.h"

CMedic_Idle_State::CMedic_Idle_State()
{
}

CMedic_Idle_State::~CMedic_Idle_State()
{
}

void CMedic_Idle_State::Initialize(CObj_Dynamic* _medic)
{
	m_pFrameCopy = _medic->Get_Frame();
	m_pFrameKeyCopy = _medic->Get_FrameKey();

	*m_pFrameKeyCopy = L"Medic_Idle";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 0;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 100;
	m_pFrameCopy->dwTime = GetTickCount();

	if (_medic->Get_Stat().m_Hp < 0)
		_medic->ChangeState(DIE_STATE);
}

int CMedic_Idle_State::Update(CObj_Dynamic* _medic)
{
	_medic->CheckEnemy();
	return 0;
}

void CMedic_Idle_State::Late_Update(CObj_Dynamic*)
{
}

void CMedic_Idle_State::Render(CObj_Dynamic*, HDC hDC)
{
}

void CMedic_Idle_State::Release(CObj_Dynamic*)
{
}

void CMedic_Idle_State::Move_Frame(CObj_Dynamic*)
{
}
