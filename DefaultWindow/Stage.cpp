#include "stdafx.h"
#include "Stage.h"
#include "LineMgr.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "Monster.h"
#include "Scv.h"
#include "StateMgr.h"
#include "Marine.h"
#include "SpawnMgr.h"
CStage::CStage()
{
}


CStage::~CStage()
{
	Release();
}

void CStage::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/Tile.bmp", L"Tile");
	CTileMgr::Get_Instance()->Load_Tile();
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ground.bmp", L"Ground");

	InitSpawn();
}

int CStage::Update()
{
	CTileMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();

	return 0;
}

void CStage::Late_Update()
{
	CTileMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
	Key_Input();
}

void CStage::Render(HDC hDC)
{
	HDC	hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground");

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
}

void CStage::Release()
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
}

void CStage::InitSpawn()
{
	CObj_Dynamic* scv1 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CScv>(OBJ_SCV, 200.f, 200.f);
	CObj_Dynamic* scv2 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CScv>(OBJ_SCV, ATTACK_STATE, 200.f, 300.f);

	CObj_Dynamic* marine1 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMarine>(OBJ_MARINE, 300.f, 200.f);
	CObj_Dynamic* marine2 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMarine>(OBJ_MARINE, WALK_STATE, 300.f, 300.f);
	CObj_Dynamic* marine3 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMarine>(OBJ_MARINE, ATTACK_STATE, 300.f, 400.f);
	CObj_Dynamic* marine4 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMarine>(OBJ_MARINE, DIE_STATE, 300.f, 500.f);
}


void CStage::Key_Input()
{
	float fY(0.f);

	if (GetAsyncKeyState(VK_RIGHT))
	{
		CScrollMgr::Get_Instance()->Set_ScrollX(-5.f);
	}

	else if (GetAsyncKeyState(VK_LEFT))
	{
		CScrollMgr::Get_Instance()->Set_ScrollX(5.f);
	}

	else if (GetAsyncKeyState(VK_UP))
	{
		CScrollMgr::Get_Instance()->Set_ScrollY(5.f);

	}

	else if (GetAsyncKeyState(VK_DOWN))
	{
		CScrollMgr::Get_Instance()->Set_ScrollY(-5.f);
	}
}