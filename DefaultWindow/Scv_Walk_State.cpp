#include "stdafx.h"
#include "Scv_Walk_State.h"
#include "TileMgr.h"
CScv_Walk_State::CScv_Walk_State()
{
}

CScv_Walk_State::~CScv_Walk_State()
{
}

void CScv_Walk_State::Initialize(CObj_Dynamic* _scv)
{
	m_pFrameCopy = _scv->Get_Frame();
	m_pFrameKeyCopy = _scv->Get_FrameKey();

	*m_pFrameKeyCopy = L"SCV_IDLE";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 5;
	m_pFrameCopy->iMotion = 1;
	m_pFrameCopy->dwSpeed = 200;
	m_pFrameCopy->dwTime = GetTickCount();


	POINT scvPoint = _scv->GetMousePT();
	INFO info = _scv->Get_Info();

	int ScvX = info.fX / TILECX;
	int ScvY = info.fY / TILECY;

	int	TileX = scvPoint.x / TILECX;
	int	TileY = scvPoint.y / TILECY;

	IWalkState::Set_Astar(ScvX, ScvY, TileX, TileY);
}

int CScv_Walk_State::Update(CObj_Dynamic*)
{
	return OBJ_NOEVENT;
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

void CScv_Walk_State::Move_Frame()
{
}
