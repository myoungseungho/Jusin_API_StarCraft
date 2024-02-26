#include "stdafx.h"
#include "Stage.h"
#include "LineMgr.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "Scv.h"
#include "Marine.h"
#include "SpawnMgr.h"
#include "FireBat.h"
#include "Medic.h"
#include "Tank.h"
#include "Mouse.h"
#include "AStarMgr.h"
#include "KeyMgr.h"
#include "Obj_Static.h"
#include "Center.h"
#include "Mineral.h"
#include "SupplyDepot.h"
#include "Barrack.h"
#include "Factory.h"
#include "Starport.h"
#include "TechTreeMgr.h"
CStage::CStage()
{
}


CStage::~CStage()
{
	Release();
}

void CStage::Initialize()
{
	CTileMgr::Get_Instance()->Load_Tile();
	CAStarMgr::Get_Instance()->Initialize();
	CKeyMgr::Get_Instance()->Initialize();
	CTechTreeMgr::Get_Instance()->Initialize();
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/Grid.bmp", L"Grid");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Single/MainMap.bmp", L"MainMap");

	Init_Obj_Spawn();
}

int CStage::Update()
{
	CKeyMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();

	return 0;
}

void CStage::Late_Update()
{
	CKeyMgr::Get_Instance()->Late_Update();
	CTileMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage::Render(HDC hDC)
{
	HDC	hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"MainMap");

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC,
		iScrollX, iScrollY, MAPCX, MAPCY,
		hGroundDC,
		0,
		0,
		SRCCOPY);

	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);

	HDC	hUIDC = CBmpMgr::Get_Instance()->Find_Image(L"MainUI");
	GdiTransparentBlt(
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		0, // 복사 받을 위치 좌표
		0,
		WINCX,	// 복사 받을 이미지의 가로, 세로
		WINCY,
		hUIDC,		// 비트맵을 가지고 있는 DC
		0,			// 비트맵 출력 시작 좌표 LEFT, TOP
		0,
		WINCX,	// 출력할 비트맵 가로
		WINCY,	// 출력할 비트맵 세로
		RGB(0, 0, 0));	// 제거할 색상 값

	m_Mouse->Render(hDC);
}

void CStage::Release()
{
	CObjMgr::Get_Instance()->Delete_ID_DynamicObj(DYANMIC_OBJ_SCV);
	CObjMgr::Get_Instance()->Delete_ID_DynamicObj(DYNAMIC_OBJ_MARINE);
	CObjMgr::Get_Instance()->Delete_ID_DynamicObj(DYNAMIC_OBJ_FIREBAT);
	CObjMgr::Get_Instance()->Delete_ID_DynamicObj(DYNAMIC_OBJ_MEDIC);
	CObjMgr::Get_Instance()->Delete_ID_DynamicObj(DYNAMIC_OBJ_TANK);
}

void CStage::Init_Obj_Spawn()
{
	m_Mouse = CSpawnMgr::Get_Instance()->Spawn_UIObj<CMouse>(UI_OBJ_MOUSE);
	CObj_Dynamic* scv1 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CScv>(DYANMIC_OBJ_SCV, FACTION_ALLY, 200.f, 200.f);
	CObj_Dynamic* scv2 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CScv>(DYANMIC_OBJ_SCV, FACTION_ALLY, 300.f, 200.f);
	CObj_Dynamic* scv3 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CScv>(DYANMIC_OBJ_SCV, FACTION_ALLY, 400.f, 200.f);

	CObj_Static* center = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CCenter>(STATIC_OBJ_CENTER, FACTION_ALLY, 300.f, 300.f);
	CObj_Static* depot = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CSupplyDepot>(STATIC_OBJ_DEPOT, FACTION_ALLY, 500.f, 300.f);
	CObj_Static* barrack = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CBarrack>(STATIC_OBJ_BARRACK, FACTION_ALLY, 500.f, 500.f);
	CObj_Static* cfactory = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CFactory>(STATIC_OBJ_FACTORY, FACTION_ALLY, 500.f, 700.f);
	CObj_Static* starport = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CStarport>(STATIC_OBJ_STARPORT, FACTION_ALLY, 700.f, 300.f);


	CObj_Static* mineral1 = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CMineral>(STATIC_OBJ_MINERAL, FACTION_RESOURCE, 130.f, 100.f);
	CObj_Static* mineral2 = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CMineral>(STATIC_OBJ_MINERAL, FACTION_RESOURCE, 100.f, 150.f);
	CObj_Static* mineral3 = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CMineral>(STATIC_OBJ_MINERAL, FACTION_RESOURCE, 130.f, 200.f);
	CObj_Static* mineral4 = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CMineral>(STATIC_OBJ_MINERAL, FACTION_RESOURCE, 100.f, 250.f);
	CObj_Static* mineral5 = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CMineral>(STATIC_OBJ_MINERAL, FACTION_RESOURCE, 130.f, 300.f);
	CObj_Static* mineral6 = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CMineral>(STATIC_OBJ_MINERAL, FACTION_RESOURCE, 100.f, 350.f);
	CObj_Static* mineral7 = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CMineral>(STATIC_OBJ_MINERAL, FACTION_RESOURCE, 130.f, 400.f);


	//CObj_Dynamic* marine1 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMarine>(OBJ_MARINE, 300.f, 200.f);
	//CObj_Dynamic* marine2 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMarine>(OBJ_MARINE, WALK_STATE, 300.f, 300.f);
	//CObj_Dynamic* marine3 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMarine>(OBJ_MARINE, ATTACK_STATE, 300.f, 400.f);
	//CObj_Dynamic* marine4 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMarine>(OBJ_MARINE, DIE_STATE, 300.f, 500.f);

	//CObj_Dynamic* fireBat1 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CFireBat>(OBJ_FIREBAT, 400.f, 200.f);
	//CObj_Dynamic* fireBat2 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CFireBat>(OBJ_FIREBAT, WALK_STATE, 400.f, 300.f);
	//CObj_Dynamic* fireBat3 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CFireBat>(OBJ_FIREBAT, ATTACK_STATE, 400.f, 400.f);

	//CObj_Dynamic* medic1 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMedic>(OBJ_MEDIC, 500.f, 200.f);
	//CObj_Dynamic* medic2 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMedic>(OBJ_MEDIC, WALK_STATE, 500.f, 300.f);
	//CObj_Dynamic* medic3 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMedic>(OBJ_MEDIC, ATTACK_STATE, 500.f, 400.f);
	//CObj_Dynamic* medic4 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMedic>(OBJ_MEDIC, DIE_STATE, 500.f, 500.f);

	//CObj_Dynamic* tank = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CTank>(OBJ_TANK, WALK_STATE, 600.f, 200.f);
}