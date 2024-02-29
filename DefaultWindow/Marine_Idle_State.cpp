#include "stdafx.h"
#include "Marine_Idle_State.h"

CMarine_Idle_State::CMarine_Idle_State()
{
}

CMarine_Idle_State::~CMarine_Idle_State()
{
}

void CMarine_Idle_State::Initialize(CObj_Dynamic* _marine)
{
	m_pFrameCopy = _marine->Get_Frame();
	m_pFrameKeyCopy = _marine->Get_FrameKey();

	*m_pFrameKeyCopy = L"MARINE_DOWNLEFT";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 0;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 200;
	m_pFrameCopy->dwTime = GetTickCount();
}

int CMarine_Idle_State::Update(CObj_Dynamic* _marine)
{
	_marine->CheckEnemy();
	return 0;
}

void CMarine_Idle_State::Late_Update(CObj_Dynamic*)
{
}

void CMarine_Idle_State::Render(CObj_Dynamic*, HDC hDC)
{
}

void CMarine_Idle_State::Release(CObj_Dynamic*)
{
}

void CMarine_Idle_State::Move_Frame(CObj_Dynamic*)
{
}
