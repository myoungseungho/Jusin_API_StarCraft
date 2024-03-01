#include "stdafx.h"
#include "UI_StarPort.h"
#include "BmpMgr.h"

CUI_StarPort_Icon::CUI_StarPort_Icon()
{
	InsertBmpFile();
}

CUI_StarPort_Icon::~CUI_StarPort_Icon()
{
	Release();
}

void CUI_StarPort_Icon::Initialize()
{
	//처음 크기 고정
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	__super::Update_Rect();

	m_pFrameKey = L"StarPort_Icon";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_UI;
}

int CUI_StarPort_Icon::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	return 0;
}

void CUI_StarPort_Icon::Late_Update()
{
}

void CUI_StarPort_Icon::Render(HDC hDC)
{
	CObj_UI::Render(hDC);
}

void CUI_StarPort_Icon::Release()
{
}

void CUI_StarPort_Icon::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CmdIcon/AdvancedBuilding/StarPort_Icon.bmp", L"StarPort_Icon");
}

UIOBJECTTYPE CUI_StarPort_Icon::GetType() const
{
	return UI_OBJECT_ICON;
}

int CUI_StarPort_Icon::GetDetailType() const
{
	return ICON_STARPORT;
}
