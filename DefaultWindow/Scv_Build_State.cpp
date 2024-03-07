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
#include "TechTreeMgr.h"
#include "SoundMgr.h"
#include "EconomyMgr.h"
#include "Academy.h"
#include "BmpMgr.h"
#include "Science_Facility.h"
CScv_Build_State::CScv_Build_State() : m_build_Start(false), m_Building(nullptr)
{
}

CScv_Build_State::~CScv_Build_State()
{
}

void CScv_Build_State::Initialize(CObj_Dynamic* _scv)
{
	m_pFrameCopy = _scv->Get_Frame();
	m_pFrameKeyCopy = _scv->Get_FrameKey();

	*m_pFrameKeyCopy = L"SCV_DOWNLEFT";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 16;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 200;
	m_pFrameCopy->dwTime = GetTickCount();

	m_pFrameKey_Attack = L"SCV_Bullet";
	m_tFrame_Attack.iFrameStart = 0;
	m_tFrame_Attack.iFrameEnd = 9;
	m_tFrame_Attack.iMotion = 0;
	m_tFrame_Attack.dwSpeed = 50;
	m_tFrame_Attack.dwTime = GetTickCount();

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
		BuildStart(_scv);
		m_build_Start = true;
	}

	if (m_build_Start)
	{
		SCV_Build_Move(_scv);
	}

	//건물이 소환되었고 완료되면
	if (m_Building != nullptr && m_Building->GetIsCompleteBuilding())
	{
		m_Building = nullptr;
		m_build_Start = false;
		_scv->Set_CollisionState(COLLISION_OK);
		_scv->ChangeState(IDLE_STATE);

		vector<wchar_t*> m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound(DYNAMIC_OBJ_SCV, SOUND_BUILD_COMPLETE);
		CSoundMgr::Get_Instance()->PlaySound(m_UnitSound.back(), SOUND_SCV_BUILD_COMPLETE, 1);
	}

	return 0;
}

void CScv_Build_State::Late_Update(CObj_Dynamic* _scv)
{
	Move_Frame(_scv);
}

void CScv_Build_State::Render(CObj_Dynamic* _scv, HDC hDC)
{
	if (m_build_Start)
	{
		int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		HDC	hBulletDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey_Attack);

		GdiTransparentBlt(
			hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
			(_scv->Get_Rect().left + iScrollX), // 복사 받을 위치 좌표
			(_scv->Get_Rect().top + iScrollY),
			48,	// 복사 받을 이미지의 가로, 세로
			48,
			hBulletDC,		// 비트맵을 가지고 있는 DC
			48 * m_tFrame_Attack.iFrameStart,			// 비트맵 출력 시작 좌표 LEFT, TOP
			48 * m_tFrame_Attack.iMotion,
			48,	// 출력할 비트맵 가로
			48,	// 출력할 비트맵 세로
			RGB(0, 0, 0));	// 제거할 색상 값
	}
}

void CScv_Build_State::Release(CObj_Dynamic* _scv)
{

}

void CScv_Build_State::BuildStart(CObj_Dynamic* _scv)
{
	UI_BUILDINGSTATE buildState = CUIMgr::Get_Instance()->GetBuilding();

	if (buildState != UI_STATIC_OBJ_END)
	{
		POINT mousePT = _scv->GetMousePT();
		_scv->Set_CollisionState(COLLISION_NOT);

		switch (buildState)
		{
		case STATIC_OBJ_CENTER:
			m_Building = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CCenter>(STATIC_OBJ_CENTER, FACTION_ALLY, mousePT.x, mousePT.y);
			CEconomyMgr::Get_Instance()->SetMineral(-400);
			break;
		case STATIC_OBJ_DEPOT:
			m_Building = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CSupplyDepot>(STATIC_OBJ_DEPOT, FACTION_ALLY, mousePT.x, mousePT.y);
			CEconomyMgr::Get_Instance()->SetMineral(-100);
			CEconomyMgr::Get_Instance()->SetMaxPeople();
			break;
		case STATIC_OBJ_BARRACK:
			m_Building = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CBarrack>(STATIC_OBJ_BARRACK, FACTION_ALLY, mousePT.x, mousePT.y);
			CTechTreeMgr::Get_Instance()->SetBuiding(STATIC_OBJ_BARRACK);
			CEconomyMgr::Get_Instance()->SetMineral(-150);
			break;
		case STATIC_OBJ_ACADENY:
			m_Building = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CAcademy>(STATIC_OBJ_ACADENY, FACTION_ALLY, mousePT.x, mousePT.y);
			CTechTreeMgr::Get_Instance()->SetBuiding(STATIC_OBJ_ACADENY);
			CTechTreeMgr::Get_Instance()->SetIsAcademy();
			CEconomyMgr::Get_Instance()->SetMineral(-150);
			break;
		case STATIC_OBJ_FACTORY:
			m_Building = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CFactory>(STATIC_OBJ_FACTORY, FACTION_ALLY, mousePT.x, mousePT.y);
			CTechTreeMgr::Get_Instance()->SetBuiding(STATIC_OBJ_FACTORY);
			CEconomyMgr::Get_Instance()->SetMineral(-200);
			CEconomyMgr::Get_Instance()->SetGas(-100);
			break;
		case STATIC_OBJ_STARPORT:
			m_Building = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CStarport>(STATIC_OBJ_STARPORT, FACTION_ALLY, mousePT.x, mousePT.y);
			CTechTreeMgr::Get_Instance()->SetBuiding(STATIC_OBJ_STARPORT);
			CEconomyMgr::Get_Instance()->SetMineral(-150);
			CEconomyMgr::Get_Instance()->SetGas(-100);
			break;
		case STATIC_OBJ_SCIENCE_FACILITY:
			m_Building = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CScience_Facility>(STATIC_OBJ_SCIENCE_FACILITY, FACTION_ALLY, mousePT.x, mousePT.y);
			CTechTreeMgr::Get_Instance()->SetBuiding(STATIC_OBJ_SCIENCE_FACILITY);
			CEconomyMgr::Get_Instance()->SetMineral(-100);
			CEconomyMgr::Get_Instance()->SetGas(-150);
			break;
		case STATIC_OBJ_MINERAL:
			break;
		case STATIC_OBJ_END:
			break;
		default:
			break;
		}


		//_scv->Set_CollisionState(COLLISION_OK);
		//_scv->ChangeStateWithMouse(mousePT, IDLE_STATE);
		CUIMgr::Get_Instance()->SetClear_CurrentBuilding();
	}
}

void CScv_Build_State::SCV_Build_Move(CObj_Dynamic* _scv)
{
	if (m_Building == nullptr)
		return;

	float unitX = _scv->Get_Info().fX;
	float unitY = _scv->Get_Info().fY;

	// 현재 목표 타일의 중심 좌표 계산
	float targetX = m_Building->Get_Info().fX;
	float targetY = m_Building->Get_Info().fY;

	// 이동해야 할 방향 벡터 계산
	float dirX = targetX - unitX;
	float dirY = targetY - unitY;
	float radian = atan2(dirY, dirX);
	float degree = (radian * 180) / PI;
	float length = sqrt(dirX * dirX + dirY * dirY);

	// 단위 방향 벡터와 속도를 사용하여 이동
	float speed = /*_scv->Get_Stat().m_fSpeed*/1.f; // 적당한 속도 값
	if (length > speed) { // 목표까지의 거리가 속도보다 클 경우, 이동 실행
		dirX = (dirX / length) * speed;
		dirY = (dirY / length) * speed;
		_scv->Set_PosX(dirX);
		_scv->Set_PosY(dirY);

		DetermineKey(_scv, degree);
	}
}
