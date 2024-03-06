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
#include "UnitControlMgr.h"
#include "UI_Menu.h"
#include "UI_MiniMap.h"
#include "UI_Resource.h"
#include "Ghost.h"
#include "Science_Facility.h"
CStage::CStage()
{
}


CStage::~CStage()
{
	Release();
}

void CStage::Initialize()
{
	Init_Bmp();
	// 난수 발생기의 초기 시드 값을 현재 시간으로 설정
	srand(static_cast<unsigned int>(time(nullptr)));
	CSoundMgr::Get_Instance()->Initialize();
	CTileMgr::Get_Instance()->Load_Tile();
	CKeyMgr::Get_Instance()->Initialize();
	CTechTreeMgr::Get_Instance()->Initialize();


	Init_Obj_Spawn();

	CUIMgr::Get_Instance()->Initialize();
	CAStarMgr::Get_Instance()->Initialize();
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
	CUnitControlMgr::Get_Instance()->Late_Update();
	CUIMgr::Get_Instance()->Late_Update();
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
	CUIMgr::Get_Instance()->Render(hDC);
}

void CStage::Release()
{
	CObjMgr::Get_Instance()->Delete_ID_DynamicObj(DYNAMIC_OBJ_SCV);
	CObjMgr::Get_Instance()->Delete_ID_DynamicObj(DYNAMIC_OBJ_MARINE);
	CObjMgr::Get_Instance()->Delete_ID_DynamicObj(DYNAMIC_OBJ_FIREBAT);
	CObjMgr::Get_Instance()->Delete_ID_DynamicObj(DYNAMIC_OBJ_MEDIC);
	CObjMgr::Get_Instance()->Delete_ID_DynamicObj(DYNAMIC_OBJ_TANK);
}

void CStage::Init_Bmp()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/Grid.bmp", L"Grid");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Single/MainMap.bmp", L"MainMap");

	//32
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/PSelect/PSelect0.bmp", L"PSelect0");
	//40
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/PSelect/PSelect1.bmp", L"PSelect1");
	//64
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/PSelect/PSelect2.bmp", L"PSelect2");
	//64, big
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/PSelect/PSelect3.bmp", L"PSelect3");
	//80
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/PSelect/PSelect4.bmp", L"PSelect4");
	//96
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/PSelect/PSelect5.bmp", L"PSelect5");
	//128
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/PSelect/PSelect6.bmp", L"PSelect6");
	//128, big
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/PSelect/PSelect7.bmp", L"PSelect7");
	//148
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/PSelect/PSelect8.bmp", L"PSelect8");
	//224
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/PSelect/PSelect9.bmp", L"PSelect9");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/ESelect/ESelect0.bmp", L"ESelect0");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/ESelect/ESelect1.bmp", L"ESelect1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/ESelect/ESelect2.bmp", L"ESelect2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/ESelect/ESelect3.bmp", L"ESelect3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/ESelect/ESelect4.bmp", L"ESelect4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/ESelect/ESelect5.bmp", L"ESelect5");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/ESelect/ESelect6.bmp", L"ESelect6");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/ESelect/ESelect7.bmp", L"ESelect7");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/ESelect/ESelect8.bmp", L"ESelect8");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/ESelect/ESelect9.bmp", L"ESelect9");
}

void CStage::Init_Obj_Spawn()
{
	Ally_Static_Obj_Spawn();
	Ally_Dynamic_Obj_Spawn();
	Enemy_Static_Obj_Spawn();
	Enemy_Dynamic_Obj_Spawn();

	CObj_UI* mainUI = CSpawnMgr::Get_Instance()->Spawn_UIObj<CBackGround>(UI_OBJECT_MAIN);
	CObj_UI* menu = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Menu>(UI_OBJECT_MAIN);
	CObj_UI* mini = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_MiniMap>(UI_OBJECT_MAIN);
	CObj_UI* resource = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Resource>(UI_OBJECT_MAIN);
	CObj_UI* mouse = CSpawnMgr::Get_Instance()->Spawn_UIObj<CMouse>(UI_OBJECT_MOUSE);
}

void CStage::Ally_Static_Obj_Spawn()
{
	CObj_Static* center = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CCenter>(STATIC_OBJ_CENTER, FACTION_ALLY, 350.f, 200.f);
	//CObj_Static* depot = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CSupplyDepot>(STATIC_OBJ_DEPOT, FACTION_ALLY, 500.f, 300.f);
	//CObj_Static* barrack = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CBarrack>(STATIC_OBJ_BARRACK, FACTION_ALLY, 500.f, 500.f);
	//CObj_Static* cfactory = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CFactory>(STATIC_OBJ_FACTORY, FACTION_ALLY, 500.f, 700.f);
	//CObj_Static* science = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CScience_Facility>(STATIC_OBJ_SCIENCE_FACILITY, FACTION_ALLY, 700.f, 300.f);

	CObj_Static* mineral1 = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CMineral>(STATIC_OBJ_MINERAL, FACTION_RESOURCE, 130.f, 100.f);
	CObj_Static* mineral2 = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CMineral>(STATIC_OBJ_MINERAL, FACTION_RESOURCE, 100.f, 150.f);
	CObj_Static* mineral3 = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CMineral>(STATIC_OBJ_MINERAL, FACTION_RESOURCE, 130.f, 200.f);
	CObj_Static* mineral4 = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CMineral>(STATIC_OBJ_MINERAL, FACTION_RESOURCE, 100.f, 250.f);
	CObj_Static* mineral5 = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CMineral>(STATIC_OBJ_MINERAL, FACTION_RESOURCE, 130.f, 300.f);
	CObj_Static* mineral6 = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CMineral>(STATIC_OBJ_MINERAL, FACTION_RESOURCE, 100.f, 350.f);
	CObj_Static* mineral7 = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CMineral>(STATIC_OBJ_MINERAL, FACTION_RESOURCE, 130.f, 400.f);
}

void CStage::Enemy_Static_Obj_Spawn()
{
	CObj_Static* center = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CCenter>(STATIC_OBJ_CENTER, FACTION_ENEMY, 3800.f, 3800.f);

	CObj_Static* depot1 = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CSupplyDepot>(STATIC_OBJ_DEPOT, FACTION_ENEMY, 3600, 3800.f);
	CObj_Static* depot2 = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CSupplyDepot>(STATIC_OBJ_DEPOT, FACTION_ENEMY, 3600, 3700.f);
	CObj_Static* depot3 = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CSupplyDepot>(STATIC_OBJ_DEPOT, FACTION_ENEMY, 3400, 3800.f);
	CObj_Static* depot4 = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CSupplyDepot>(STATIC_OBJ_DEPOT, FACTION_ENEMY, 3400, 3700.f);

	CObj_Static* barrack1 = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CBarrack>(STATIC_OBJ_BARRACK, FACTION_ENEMY, 3600, 3500.f);
	CObj_Static* barrack2 = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CBarrack>(STATIC_OBJ_BARRACK, FACTION_ENEMY, 3750, 3500.f);
	CObj_Static* cfactory = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CFactory>(STATIC_OBJ_FACTORY, FACTION_ENEMY, 3500.f, 3300.f);
	CObj_Static* starport = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CStarport>(STATIC_OBJ_STARPORT, FACTION_ENEMY, 3300.f, 3600.f);
}

void CStage::Ally_Dynamic_Obj_Spawn()
{
	for (size_t i = 0; i < 4; i++)
	{
		CObj_Dynamic* scv = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CScv>(DYNAMIC_OBJ_SCV, FACTION_ALLY, 340.f + i * 10.f, 270.f);

	}
	CObj_Dynamic* ghost = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CGhost>(DYNAMIC_OBJ_GHOST, FACTION_ALLY,  300.f, 400.f);

	//CObj_Dynamic* scv1 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CScv>(DYNAMIC_OBJ_SCV, FACTION_ALLY,  300.f, 300.f);
	//CObj_Dynamic* scv2 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CScv>(DYNAMIC_OBJ_SCV, FACTION_ALLY, 310.f, 300.f);
	//CObj_Dynamic* scv3 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CScv>(DYNAMIC_OBJ_SCV, FACTION_ALLY, 320.f, 300.f);
	//CObj_Dynamic* scv4 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CScv>(DYNAMIC_OBJ_SCV, FACTION_ALLY, 330.f, 300.f);


	/*CObj_Dynamic* marine = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMarine>(DYNAMIC_OBJ_MARINE, FACTION_ALLY, 300.f, 300.f);
	CObj_Dynamic* fireBat = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CFireBat>(DYNAMIC_OBJ_FIREBAT, FACTION_ALLY, 300.f, 300.f);
	CObj_Dynamic* medic = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMedic>(DYNAMIC_OBJ_MEDIC, FACTION_ALLY, 300.f, 300.f);
	CObj_Dynamic* tank = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CTank>(DYNAMIC_OBJ_TANK, FACTION_ALLY, 300.f, 300.f);*/


	//for (size_t i = 0; i < 10; i++)
	//{
	//	//CObj_Dynamic* scv1 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CScv>(DYNAMIC_OBJ_SCV, FACTION_ALLY,  300.f, 300.f + i * 30.f);
	//	CObj_Dynamic* tank = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CTank>(DYNAMIC_OBJ_TANK, FACTION_ALLY, 300.f, 300.f + i * 30.f);
	//}
}

void CStage::Enemy_Dynamic_Obj_Spawn()
{
	list<CObj_Dynamic*> enemyList;
	for (size_t i = 0; i < 20; i++)
	{
		if (i > 10)
		{
			CObj_Dynamic* marine = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMarine>(DYNAMIC_OBJ_MARINE, FACTION_ENEMY, 3500.f, 3000.f + i * 10.f);
			CObj_Dynamic* medic = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMedic>(DYNAMIC_OBJ_MEDIC, FACTION_ENEMY, 3500.f, 3000.f + i * 10.f);
			enemyList.push_back(marine);
			enemyList.push_back(medic);
		}
		else
		{
			CObj_Dynamic* fireBat = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CFireBat>(DYNAMIC_OBJ_FIREBAT, FACTION_ENEMY, 3500.f + i * 10.f, 3000.f);
			//CObj_Dynamic* tank = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CTank>(DYNAMIC_OBJ_TANK, FACTION_ENEMY, 1500.f + i * 10.f, 2000.f);

			enemyList.push_back(fireBat);
			//enemyList.push_back(tank);
		}
		CUnitControlMgr::Get_Instance()->Set_EnemyList(enemyList);
	}
}