#include "stdafx.h"
#include "UI_Build.h"
#include "BmpMgr.h"
CUI_Build_Icon::CUI_Build_Icon()
{
	InsertBmpFile();
}

CUI_Build_Icon::~CUI_Build_Icon()
{
	Release();
}

void CUI_Build_Icon::Initialize()
{
	//처음 크기 고정
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	__super::Update_Rect();

	m_pFrameKey = L"Build_Image";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_UI;
}

int CUI_Build_Icon::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	return 0;
}

void CUI_Build_Icon::Late_Update()
{
}

void CUI_Build_Icon::Render(HDC hDC)
{
	CObj_UI::Render(hDC);
}

void CUI_Build_Icon::Release()
{
}

void CUI_Build_Icon::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CmdIcon/Unituse/Build_Image.bmp", L"Build_Image");
}

UIOBJECTTYPE CUI_Build_Icon::GetType() const
{
	return UI_OBJECT_ICON;
}

int CUI_Build_Icon::GetDetailType() const
{
	return ICON_BUILD;
}
