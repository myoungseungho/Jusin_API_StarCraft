#include "stdafx.h"
#include "UI_Factyory_Addon_Wire.h"
#include "BmpMgr.h"

CUI_Factyory_Addon_Wire::CUI_Factyory_Addon_Wire()
{
    InsertBmpFile();
}

CUI_Factyory_Addon_Wire::~CUI_Factyory_Addon_Wire()
{
    Release();
}

void CUI_Factyory_Addon_Wire::Initialize()
{
	//처음 크기 고정
	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 64.f;
	__super::Update_Rect();

	m_pFrameKey = L"Machines_Big_Wire";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_UI;
}

int CUI_Factyory_Addon_Wire::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	return 0;
}

void CUI_Factyory_Addon_Wire::Late_Update()
{
}

void CUI_Factyory_Addon_Wire::Render(HDC hDC)
{
	CObj_UI::Render(hDC);
}

void CUI_Factyory_Addon_Wire::Release()
{
}

UIOBJECTTYPE CUI_Factyory_Addon_Wire::GetType() const
{
	return UI_OBJECT_WIRE;
}

int CUI_Factyory_Addon_Wire::GetDetailType() const
{
	return WIRE_FACTORY_ADDON_BIG;
}

void CUI_Factyory_Addon_Wire::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Wire/Large/Machines/Machines_Big_Wire.bmp", L"Machines_Big_Wire");
}
