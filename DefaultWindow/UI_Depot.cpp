#include "stdafx.h"
#include "UI_Depot.h"
#include "BmpMgr.h"
CUI_Depot_Icon::CUI_Depot_Icon()
{
	InsertBmpFile();
}

CUI_Depot_Icon::~CUI_Depot_Icon()
{
	Release();
}

void CUI_Depot_Icon::Initialize()
{
	m_pFrameKey = L"Depot_Icon";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();
}

int CUI_Depot_Icon::Update()
{
    return 0;
}

void CUI_Depot_Icon::Late_Update()
{
}

void CUI_Depot_Icon::Render(HDC hDC)
{
}

void CUI_Depot_Icon::Release()
{
}

void CUI_Depot_Icon::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CmdIcon/BasicBuilding/Depot_Icon.bmp", L"Depot_Icon");
}
