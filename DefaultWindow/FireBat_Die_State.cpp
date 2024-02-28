#include "stdafx.h"
#include "FireBat_Die_State.h"

CFireBat_Die_State::CFireBat_Die_State()
{
}

CFireBat_Die_State::~CFireBat_Die_State()
{
}

void CFireBat_Die_State::Initialize(CObj_Dynamic* _fireBat)
{
	m_pFrameCopy = _fireBat->Get_Frame();
	m_pFrameKeyCopy = _fireBat->Get_FrameKey();

	*m_pFrameKeyCopy = L"FireBat_Die";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 9;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 30;
	m_pFrameCopy->dwTime = GetTickCount();
}

int CFireBat_Die_State::Update(CObj_Dynamic* _fireBat)
{
	m_pFrameCopy = _fireBat->Get_Frame();
	if (m_pFrameCopy->iFrameStart == m_pFrameCopy->iFrameEnd)
		_fireBat->Set_Dead();
	return 0;
}

void CFireBat_Die_State::Late_Update(CObj_Dynamic*)
{
}

void CFireBat_Die_State::Render(CObj_Dynamic*, HDC hDC)
{
}

void CFireBat_Die_State::Release(CObj_Dynamic*)
{
}

void CFireBat_Die_State::Move_Frame(CObj_Dynamic*)
{

}
