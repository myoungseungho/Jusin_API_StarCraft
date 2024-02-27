#include "stdafx.h"
#include "Scv_Build_State.h"
#include "TileMgr.h"
#include "Define.h"
#include "UIMgr.h"
#include "SpawnMgr.h"
#include "Center.h"
#include "SupplyDepot.h"
#include "Barrack.h"
#include "Factory.h"
#include "Starport.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
CScv_Build_State::CScv_Build_State() : m_build_Start(false)
{
}

CScv_Build_State::~CScv_Build_State()
{
}

void CScv_Build_State::Initialize(CObj_Dynamic* _scv)
{
	m_pFrameCopy = _scv->Get_Frame();
	m_pFrameKeyCopy = _scv->Get_FrameKey();

	*m_pFrameKeyCopy = L"SCV_IDLE";
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
}

int CScv_Build_State::Update(CObj_Dynamic* _scv)
{
	if (Move(_scv) == MOVE_OK && !m_build_Start)
	{
		m_build_Start = true;
		Build(_scv);
	}

	return 0;
}

void CScv_Build_State::Late_Update(CObj_Dynamic*)
{
}

void CScv_Build_State::Render(CObj_Dynamic*, HDC hDC)
{
}

void CScv_Build_State::Release(CObj_Dynamic*)
{
}

void CScv_Build_State::Build(CObj_Dynamic* _scv)
{
	UI_BUILDINGSTATE buildState = CUIMgr::Get_Instance()->GetBuilding();

	if (buildState != UI_STATIC_OBJ_END)
	{
		POINT mousePT = _scv->GetMousePT();
		CObj_Static* build;

		switch (buildState)
		{
		case STATIC_OBJ_CENTER:
			build = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CCenter>(STATIC_OBJ_CENTER, FACTION_ALLY, mousePT.x, mousePT.y);
			break;
		case STATIC_OBJ_DEPOT:
			build = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CSupplyDepot>(STATIC_OBJ_DEPOT, FACTION_ALLY, mousePT.x, mousePT.y);
			break;
		case STATIC_OBJ_BARRACK:
			build = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CBarrack>(STATIC_OBJ_BARRACK, FACTION_ALLY, mousePT.x, mousePT.y);
			break;
		case STATIC_OBJ_FACTORY:
			build = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CFactory>(STATIC_OBJ_FACTORY, FACTION_ALLY, mousePT.x, mousePT.y);
			break;
		case STATIC_OBJ_STARPORT:
			build = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CStarport>(STATIC_OBJ_STARPORT, FACTION_ALLY, mousePT.x, mousePT.y);
			break;
		case STATIC_OBJ_MINERAL:
			break;
		case STATIC_OBJ_END:
			break;
		default:
			break;
		}

		_scv->Set_CollisionState(COLLISION_OK);
		_scv->ChangeStateWithMouse(mousePT, IDLE_STATE);
		CUIMgr::Get_Instance()->SetClear_CurrentBuilding();
		m_build_Start = false;
	}
}
