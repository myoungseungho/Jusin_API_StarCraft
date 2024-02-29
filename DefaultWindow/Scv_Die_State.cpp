#include "stdafx.h"
#include "Scv_Die_State.h"

CScv_Die_State::CScv_Die_State()
{
}

CScv_Die_State::~CScv_Die_State()
{
}

void CScv_Die_State::Initialize(CObj_Dynamic* _scv)
{
	m_pFrameCopy = _scv->Get_Frame();
	m_pFrameKeyCopy = _scv->Get_FrameKey();

	*m_pFrameKeyCopy = L"SCV_Die";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 9;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 30;
	m_pFrameCopy->dwTime = GetTickCount();
}

int CScv_Die_State::Update(CObj_Dynamic* _scv)
{
	m_pFrameCopy = _scv->Get_Frame();
	if (m_pFrameCopy->iFrameStart == m_pFrameCopy->iFrameEnd)
		_scv->Set_Dead();
    return 0;
}

void CScv_Die_State::Late_Update(CObj_Dynamic*)
{
}

void CScv_Die_State::Render(CObj_Dynamic*, HDC hDC)
{
}

void CScv_Die_State::Release(CObj_Dynamic*)
{
}

void CScv_Die_State::Move_Frame(CObj_Dynamic*)
{
}
