#include "stdafx.h"
#include "WalkState.h"
#include "AStarMgr.h"
#include "TileMgr.h"

IWalkState::IWalkState()
{
}

IWalkState::~IWalkState()
{
}


void IWalkState::Initialize(CObj_Dynamic* _unit)
{
	POINT scvPoint = _unit->GetMousePT();
	INFO info = _unit->Get_Info();

	int ScvX = info.fX / TILECX;
	int ScvY = info.fY / TILECY;

	int	TileX = scvPoint.x / TILECX;
	int	TileY = scvPoint.y / TILECY;

	Set_Astar(ScvX, ScvY, TileX, TileY);

	m_listPathTile = CTileMgr::Get_Instance()->GetListPath(m_Path);
}

int IWalkState::Update(CObj_Dynamic* _unit)
{
	return 0;
}

void IWalkState::Late_Update(CObj_Dynamic*)
{
}

void IWalkState::Render(CObj_Dynamic*, HDC hDC)
{
}

void IWalkState::Release(CObj_Dynamic*)
{
}

void IWalkState::Move_Frame(CObj_Dynamic*)
{
}
