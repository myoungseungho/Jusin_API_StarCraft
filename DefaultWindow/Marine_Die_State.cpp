#include "stdafx.h"
#include "Marine_Die_State.h"

CMarine_Die_State::CMarine_Die_State()
{
}

CMarine_Die_State::~CMarine_Die_State()
{
}

void CMarine_Die_State::Initialize(CObj_Dynamic* _marine)
{
	m_pFrameCopy = _marine->Get_Frame();
	m_pFrameKeyCopy = _marine->Get_FrameKey();

	*m_pFrameKeyCopy = L"Marine_Dead";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 7;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 50;
	m_pFrameCopy->dwTime = GetTickCount();
}

int CMarine_Die_State::Update(CObj_Dynamic*)
{
	return 0;
}

void CMarine_Die_State::Late_Update(CObj_Dynamic*)
{
}

void CMarine_Die_State::Render(CObj_Dynamic*, HDC hDC)
{
}

void CMarine_Die_State::Release(CObj_Dynamic*)
{
}
