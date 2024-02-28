#include "stdafx.h"
#include "FireBat_Idle_State.h"

CFireBat_Idle_State::CFireBat_Idle_State()
{
}

CFireBat_Idle_State::~CFireBat_Idle_State()
{
}

void CFireBat_Idle_State::Initialize(CObj_Dynamic* _fireBat)
{
	m_pFrameCopy = _fireBat->Get_Frame();
	m_pFrameKeyCopy = _fireBat->Get_FrameKey();

	*m_pFrameKeyCopy = L"Firebat_Idle";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 16;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 100;
	m_pFrameCopy->dwTime = GetTickCount();
}

int CFireBat_Idle_State::Update(CObj_Dynamic* _fireBat)
{
	if (m_dwTime + 1000 < GetTickCount())
	{
		_fireBat->CheckEnemy();
		m_dwTime = GetTickCount();
	}
	return 0;
}

void CFireBat_Idle_State::Late_Update(CObj_Dynamic*)
{
}

void CFireBat_Idle_State::Render(CObj_Dynamic*, HDC hDC)
{
}

void CFireBat_Idle_State::Release(CObj_Dynamic*)
{
}

void CFireBat_Idle_State::Move_Frame(CObj_Dynamic*)
{
}
