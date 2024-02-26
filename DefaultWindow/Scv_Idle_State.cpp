#include "stdafx.h"
#include "Scv_Idle_State.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
CScv_Idle_State::CScv_Idle_State()
{
}

CScv_Idle_State::~CScv_Idle_State()
{
}

void CScv_Idle_State::Initialize(CObj_Dynamic* _scv)
{
	IIdleState::Initialize(_scv);

	m_pFrameCopy = _scv->Get_Frame();
	m_pFrameKeyCopy = _scv->Get_FrameKey();

	*m_pFrameKeyCopy = L"SCV_IDLE";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 16;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 200;
	m_pFrameCopy->dwTime = GetTickCount();
}

int CScv_Idle_State::Update(CObj_Dynamic*)
{
	return 0;
}

void CScv_Idle_State::Late_Update(CObj_Dynamic* _scv)
{
}

void CScv_Idle_State::Render(CObj_Dynamic* _scv, HDC hDC)
{
	
}

void CScv_Idle_State::Release(CObj_Dynamic*)
{
}

void CScv_Idle_State::Move_Frame()
{
}

