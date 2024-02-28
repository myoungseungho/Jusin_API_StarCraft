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
#include "UIMgr.h"
#include "BackGround.h"
#include "SoundMgr.h"
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
	CUIMgr::Get_Instance()->Initialize();
	CSoundMgr::Get_Instance()->Initialize();
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
	CKeyMgr::Get_Instance()->Render(hDC);
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
	Static_Obj_Spawn();
	Ally_Obj_Spawn();
	Enemy_Obj_Spawn();

	CObj_UI* mainUI = CSpawnMgr::Get_Instance()->Spawn_UIObj<CBackGround>(UI_OBJ_MAINUI);
	CObj_UI* mouse = CSpawnMgr::Get_Instance()->Spawn_UIObj<CMouse>(UI_OBJ_MOUSE);
}

void CStage::Static_Obj_Spawn()
{
	//CObj_Static* center = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CCenter>(STATIC_OBJ_CENTER, FACTION_ALLY, 300.f, 300.f);
	//CObj_Static* depot = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CSupplyDepot>(STATIC_OBJ_DEPOT, FACTION_ALLY, 500.f, 300.f);
	//CObj_Static* barrack = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CBarrack>(STATIC_OBJ_BARRACK, FACTION_ALLY, 500.f, 500.f);
	//CObj_Static* cfactory = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CFactory>(STATIC_OBJ_FACTORY, FACTION_ALLY, 500.f, 700.f);
	//CObj_Static* starport = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CStarport>(STATIC_OBJ_STARPORT, FACTION_ALLY, 700.f, 300.f);

	/*CObj_Static* mineral1 = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CMineral>(STATIC_OBJ_MINERAL, FACTION_RESOURCE, 130.f, 100.f);
	CObj_Static* mineral2 = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CMineral>(STATIC_OBJ_MINERAL, FACTION_RESOURCE, 100.f, 150.f);
	CObj_Static* mineral3 = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CMineral>(STATIC_OBJ_MINERAL, FACTION_RESOURCE, 130.f, 200.f);
	CObj_Static* mineral4 = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CMineral>(STATIC_OBJ_MINERAL, FACTION_RESOURCE, 100.f, 250.f);
	CObj_Static* mineral5 = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CMineral>(STATIC_OBJ_MINERAL, FACTION_RESOURCE, 130.f, 300.f);
	CObj_Static* mineral6 = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CMineral>(STATIC_OBJ_MINERAL, FACTION_RESOURCE, 100.f, 350.f);
	CObj_Static* mineral7 = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CMineral>(STATIC_OBJ_MINERAL, FACTION_RESOURCE, 130.f, 400.f);*/
}

void CStage::Ally_Obj_Spawn()
{
	for (size_t i = 0; i < 15; i++)
	{
		CObj_Dynamic* marine = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMarine>(DYNAMIC_OBJ_MARINE, FACTION_ALLY, 200.f + i * 10.f, 300.f);
		//CObj_Dynamic* fireBat = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CFireBat>(DYNAMIC_OBJ_FIREBAT, FACTION_ALLY, 200.f + i * 10.f, 400.f);
	}

	/*CObj_Dynamic* marine1 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMarine>(DYNAMIC_OBJ_MARINE, FACTION_ALLY, 200.f, 300.f);
	CObj_Dynamic* fireBat1 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CFireBat>(DYNAMIC_OBJ_FIREBAT, FACTION_ALLY, 200.f, 400.f);*/
	//CObj_Dynamic* tank1 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CTank>(DYNAMIC_OBJ_TANK, FACTION_ALLY, 200.f, 500.f);

	//CObj_Dynamic* scv1 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CScv>(DYANMIC_OBJ_SCV, FACTION_ALLY, 200.f, 200.f);
	//CObj_Dynamic* scv2 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CScv>(DYANMIC_OBJ_SCV, FACTION_ALLY, 300.f, 200.f);
	//CObj_Dynamic* scv3 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CScv>(DYANMIC_OBJ_SCV, FACTION_ALLY, 400.f, 200.f);
}

void CStage::Enemy_Obj_Spawn()
{
	for (size_t i = 0; i < 15; i++)
	{
		//CObj_Dynamic* marine = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMarine>(DYNAMIC_OBJ_MARINE, FACTION_ENEMY, 700.f + i * 10.f, 300.f);
		CObj_Dynamic* fireBat = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CFireBat>(DYNAMIC_OBJ_FIREBAT, FACTION_ENEMY, 700.f + i * 10.f, 400.f);
	}
	//CObj_Dynamic* marine2 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMarine>(DYNAMIC_OBJ_MARINE, FACTION_ENEMY, 700.f, 300.f);
	//CObj_Dynamic* fireBat2 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CFireBat>(DYNAMIC_OBJ_FIREBAT, FACTION_ENEMY, 700.f, 400.f);
	//CObj_Dynamic* tank2 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CTank>(DYNAMIC_OBJ_TANK, FACTION_ENEMY, 700.f, 500.f);
}
