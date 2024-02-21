#include "stdafx.h"
#include "Scv_Attack_State.h"

CScv_Attack_State::CScv_Attack_State()
{
}

CScv_Attack_State::~CScv_Attack_State()
{
}

void CScv_Attack_State::Initialize(CObj* _scv)
{
	m_pFrameCopy = _scv->Get_Frame();
	m_pFrameKeyCopy = _scv->Get_FrameKey();

	*m_pFrameKeyCopy = L"SCV_ATTACK";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 33;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 200;
	m_pFrameCopy->dwTime = GetTickCount();
}

int CScv_Attack_State::Update(CObj* _scv)
{
    return 0;
}

void CScv_Attack_State::Late_Update(CObj* _scv)
{
}

void CScv_Attack_State::Render(CObj* _scv, HDC hDC)
{
	
}

void CScv_Attack_State::Release(CObj* _scv)
{
}
