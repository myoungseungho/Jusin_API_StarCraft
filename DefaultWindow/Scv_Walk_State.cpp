#include "stdafx.h"
#include "Scv_Walk_State.h"

CScv_Walk_State::CScv_Walk_State()
{
}

CScv_Walk_State::~CScv_Walk_State()
{
}



void CScv_Walk_State::Initialize(CObj* _scv)
{
	m_pFrameCopy = _scv->Get_Frame();
	m_pFrameKeyCopy = _scv->Get_FrameKey();

	m_pFrameKeyCopy = L"SCV_IDLE";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 5;
	m_pFrameCopy->iMotion = 1;
	m_pFrameCopy->dwSpeed = 200;
	m_pFrameCopy->dwTime = GetTickCount();
}

int CScv_Walk_State::Update(CObj*)
{
	return 0;
}

void CScv_Walk_State::Late_Update(CObj*)
{
}

void CScv_Walk_State::Render(CObj*, HDC hDC)
{
}

void CScv_Walk_State::Release(CObj*)
{
}
