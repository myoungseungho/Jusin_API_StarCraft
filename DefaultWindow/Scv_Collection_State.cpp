#include "stdafx.h"
#include "Scv_Collection_State.h"
#include "TileMgr.h"
CScv_Collection_State::CScv_Collection_State()
{
}

CScv_Collection_State::~CScv_Collection_State()
{
}

void CScv_Collection_State::Initialize(CObj_Dynamic* _scv)
{
	m_pFrameCopy = _scv->Get_Frame();
	m_pFrameKeyCopy = _scv->Get_FrameKey();

	*m_pFrameKeyCopy = L"SCV_DOWNLEFT";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 16;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 200;
	m_pFrameCopy->dwTime = GetTickCount();

    POINT scvPoint = _scv->GetMousePT();
    INFO info = _scv->Get_Info();

	int ScvX = info.fX / TILECX;
	int ScvY = info.fY / TILECY;

	int	TileX = scvPoint.x / TILECX;
	int	TileY = scvPoint.y / TILECY;

	Set_Astar(ScvX, ScvY, TileX, TileY);

	m_listPathTile = CTileMgr::Get_Instance()->GetListPath(m_Path);
	m_listPathTile.pop_back();
}

int CScv_Collection_State::Update(CObj_Dynamic* _scv)
{
	if (Move(_scv) == MOVE_OK)
	{
		Collection(_scv);
	}
    return 0;
}

void CScv_Collection_State::Late_Update(CObj_Dynamic*)
{
}

void CScv_Collection_State::Render(CObj_Dynamic*, HDC hDC)
{
}

void CScv_Collection_State::Release(CObj_Dynamic*)
{
}

void CScv_Collection_State::Collection(CObj_Dynamic* _scv)
{
}
