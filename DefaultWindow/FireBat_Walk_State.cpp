#include "stdafx.h"
#include "FireBat_Walk_State.h"
#include "TileMgr.h"

CFireBat_Walk_State::CFireBat_Walk_State()
{
}

CFireBat_Walk_State::~CFireBat_Walk_State()
{
}

void CFireBat_Walk_State::Initialize(CObj_Dynamic* _fireBat)
{
	m_pFrameCopy = _fireBat->Get_Frame();
	m_pFrameKeyCopy = _fireBat->Get_FrameKey();

	*m_pFrameKeyCopy = L"Firebat_Work_Up_Right_90";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 15;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 50;
	m_pFrameCopy->dwTime = GetTickCount();

	POINT scvPoint = _fireBat->GetMousePT();
	INFO info = _fireBat->Get_Info();

	int ScvX = info.fX / TILECX;
	int ScvY = info.fY / TILECY;

	int	TileX = scvPoint.x / TILECX;
	int	TileY = scvPoint.y / TILECY;

	Set_Astar(ScvX, ScvY, TileX, TileY);

	m_listPathTile = CTileMgr::Get_Instance()->GetListPath(m_Path);
}

int CFireBat_Walk_State::Update(CObj_Dynamic* _fireBat)
{
	if (Move(_fireBat) == MOVE_OK)
		_fireBat->ChangeState(IDLE_STATE);

	return 0;
}

void CFireBat_Walk_State::Late_Update(CObj_Dynamic*)
{
}

void CFireBat_Walk_State::Render(CObj_Dynamic*, HDC hDC)
{
}

void CFireBat_Walk_State::Release(CObj_Dynamic*)
{
}

void CFireBat_Walk_State::Move_Frame()
{
}
