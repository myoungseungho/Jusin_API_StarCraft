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
	m_pFrameCopy->iFrameEnd = 0;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 100;
	m_pFrameCopy->dwTime = GetTickCount();

	if (_fireBat->Get_Stat().m_Hp < 0)
		_fireBat->ChangeState(DIE_STATE);
}

int CFireBat_Idle_State::Update(CObj_Dynamic* _fireBat)
{

	_fireBat->CheckEnemy();
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
