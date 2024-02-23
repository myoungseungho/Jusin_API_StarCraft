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
#include "FireBat.h"
#include "Medic.h"
#include "Tank.h"
#include "Mouse.h"
#include "AStarMgr.h"
CStage::CStage() : m_Cursor_Speed(0.f)
{
}


CStage::~CStage()
{
	Release();
}

void CStage::Initialize()
{
	m_Cursor_Speed = 12.f;

	CTileMgr::Get_Instance()->Load_Tile();
	CAStarMgr::Get_Instance()->Initialize();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/Grid.bmp", L"Grid");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Single/MainMap.bmp", L"MainMap");

	CObj_UI* mouse = CSpawnMgr::Get_Instance()->Spawn_UIObj<CMouse>(UI_OBJ_MOUSE);
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
	OffSet();
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

	//UIâ ����
	HDC	hUIDC = CBmpMgr::Get_Instance()->Find_Image(L"MainUI");

	GdiTransparentBlt(
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		0, // ���� ���� ��ġ ��ǥ
		0,
		WINCX,	// ���� ���� �̹����� ����, ����
		WINCY,
		hUIDC,		// ��Ʈ���� ������ �ִ� DC
		0,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		0,
		WINCX,	// ����� ��Ʈ�� ����
		WINCY,	// ����� ��Ʈ�� ����
		RGB(0, 0, 0));	// ������ ���� ��
}

void CStage::Release()
{
	CObjMgr::Get_Instance()->Delete_ID_DynamicObj(DYANMIC_OBJ_SCV);
	CObjMgr::Get_Instance()->Delete_ID_DynamicObj(DYNAMIC_OBJ_MARINE);
	CObjMgr::Get_Instance()->Delete_ID_DynamicObj(DYNAMIC_OBJ_FIREBAT);
	CObjMgr::Get_Instance()->Delete_ID_DynamicObj(DYNAMIC_OBJ_MEDIC);
	CObjMgr::Get_Instance()->Delete_ID_DynamicObj(DYNAMIC_OBJ_TANK);
}

void CStage::InitSpawn()
{
	CObj_Dynamic* scv1 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CScv>(DYANMIC_OBJ_SCV, 200.f, 200.f);
	/*CObj_Dynamic* scv2 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CScv>(OBJ_SCV, ATTACK_STATE, 200.f, 300.f);

	CObj_Dynamic* marine1 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMarine>(OBJ_MARINE, 300.f, 200.f);
	CObj_Dynamic* marine2 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMarine>(OBJ_MARINE, WALK_STATE, 300.f, 300.f);
	CObj_Dynamic* marine3 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMarine>(OBJ_MARINE, ATTACK_STATE, 300.f, 400.f);
	CObj_Dynamic* marine4 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMarine>(OBJ_MARINE, DIE_STATE, 300.f, 500.f);

	CObj_Dynamic* fireBat1 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CFireBat>(OBJ_FIREBAT, 400.f, 200.f);
	CObj_Dynamic* fireBat2 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CFireBat>(OBJ_FIREBAT, WALK_STATE, 400.f, 300.f);
	CObj_Dynamic* fireBat3 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CFireBat>(OBJ_FIREBAT, ATTACK_STATE, 400.f, 400.f);

	CObj_Dynamic* medic1 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMedic>(OBJ_MEDIC, 500.f, 200.f);
	CObj_Dynamic* medic2 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMedic>(OBJ_MEDIC, WALK_STATE, 500.f, 300.f);
	CObj_Dynamic* medic3 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMedic>(OBJ_MEDIC, ATTACK_STATE, 500.f, 400.f);
	CObj_Dynamic* medic4 = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMedic>(OBJ_MEDIC, DIE_STATE, 500.f, 500.f);

	CObj_Dynamic* tank = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CTank>(OBJ_TANK, WALK_STATE, 600.f, 200.f);*/
}


void CStage::Key_Input()
{
	float fY(0.f);

	if (GetAsyncKeyState(VK_RIGHT))
	{
		CScrollMgr::Get_Instance()->Set_ScrollX(-10.f);
	}

	else if (GetAsyncKeyState(VK_LEFT))
	{
		CScrollMgr::Get_Instance()->Set_ScrollX(10.f);
	}

	else if (GetAsyncKeyState(VK_UP))
	{
		CScrollMgr::Get_Instance()->Set_ScrollY(10.f);

	}

	else if (GetAsyncKeyState(VK_DOWN))
	{
		CScrollMgr::Get_Instance()->Set_ScrollY(-10.f);
	}
}

void CStage::OffSet()
{
	int	iOffSetMinX = 0;
	int	iOffSetMaxX = WINCX;

	int	iOffSetMinY = 0;
	int	iOffSetMaxY = WINCY;

	POINT	Pt;
	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	if (iOffSetMinX > Pt.x)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_Cursor_Speed);

	if (iOffSetMaxX < Pt.x)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_Cursor_Speed);

	if (iOffSetMinY > Pt.y)
		CScrollMgr::Get_Instance()->Set_ScrollY(m_Cursor_Speed);

	if (iOffSetMaxY < Pt.y)
		CScrollMgr::Get_Instance()->Set_ScrollY(-m_Cursor_Speed);
}