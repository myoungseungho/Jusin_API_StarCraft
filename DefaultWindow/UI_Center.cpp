#include "stdafx.h"
#include "UI_Center.h"
#include "BmpMgr.h"
CUI_Center_Icon::CUI_Center_Icon()
{
	InsertBmpFile();
}

CUI_Center_Icon::~CUI_Center_Icon()
{
	Release();
}

void CUI_Center_Icon::Initialize()
{
	//처음 크기 고정
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	__super::Update_Rect();


	m_pFrameKey = L"Center_Icon";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_UI;
}

int CUI_Center_Icon::Update()
{
    return 0;
}

void CUI_Center_Icon::Late_Update()
{
}

void CUI_Center_Icon::Render(HDC hDC)
{
	CObj_UI::Render(hDC);
}

void CUI_Center_Icon::Release()
{
}

void CUI_Center_Icon::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CmdIcon/BasicBuilding/Center_Icon.bmp", L"Center_Icon");
}
