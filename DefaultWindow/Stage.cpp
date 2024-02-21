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
}

void CStage::Render(HDC hDC)
{
	HDC	hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground");

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//BitBlt(hDC, iScrollX, iScrollY, 1920, 1280,	hGroundDC,0,0,SRCCOPY);

	//CLineMgr::Get_Instance()->Render(hDC);
	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
}

void CStage::Release()
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
}

void CStage::InitSpawn()
{
	//SDV
	CObj_Dynamic* scv1 = CAbstractFactory<CScv>::Create_Dynamic(200.f, 200.f);
	CObjMgr::Get_Instance()->Add_Dynamic_Object(OBJ_SCV, scv1);

	CObj_Dynamic* scv2 = CAbstractFactory<CScv>::Create_Dynamic(200.f, 300.f);
	static_cast<CScv*>(scv2)->ChangeState(CStateMgr::Get_Instance()->GetVecObjState(OBJ_SCV)[SCV_ATTACK]);
	CObjMgr::Get_Instance()->Add_Dynamic_Object(OBJ_SCV, scv2);
}
