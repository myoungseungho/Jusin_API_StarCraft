#include "stdafx.h"
#include "Scv_Walk_State.h"
#include "TileMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
CScv_Walk_State::CScv_Walk_State() : m_dwTime(0)
{
}

CScv_Walk_State::~CScv_Walk_State()
{
}

void CScv_Walk_State::Initialize(CObj_Dynamic* _scv)
{
	m_pFrameCopy = _scv->Get_Frame();
	m_pFrameKeyCopy = _scv->Get_FrameKey();

	*m_pFrameKeyCopy = L"SCV_DOWNLEFT";
	m_pFrameCopy->iFrameStart = 0; 
	m_pFrameCopy->iFrameEnd = 0;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 200;
	m_pFrameCopy->dwTime = GetTickCount();

	IWalkState::Initialize(_scv);
}

int CScv_Walk_State::Update(CObj_Dynamic* _scv)
{
	if (Move(_scv) == MOVE_OK)
		_scv->ChangeState(IDLE_STATE);

	return 0;
}

void CScv_Walk_State::Late_Update(CObj_Dynamic*)
{
}

void CScv_Walk_State::Render(CObj_Dynamic* _scv, HDC hDC)
{

}

void CScv_Walk_State::Release(CObj_Dynamic*)
{
}

void CScv_Walk_State::Move_Frame(CObj_Dynamic*)
{
}
