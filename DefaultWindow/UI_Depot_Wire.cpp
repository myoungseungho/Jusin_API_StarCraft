#include "stdafx.h"
#include "UI_Depot_Wire.h"
#include "BmpMgr.h"

CUI_Depot_Wire::CUI_Depot_Wire()
{
    InsertBmpFile();
}

CUI_Depot_Wire::~CUI_Depot_Wire()
{
    Release();
}

void CUI_Depot_Wire::Initialize()
{
	//처음 크기 고정
	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 64.f;
	__super::Update_Rect();

	m_pFrameKey = L"Depot_Big_Wire";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_UI;
}

int CUI_Depot_Wire::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	return 0;
}

void CUI_Depot_Wire::Late_Update()
{
}

void CUI_Depot_Wire::Render(HDC hDC)
{
	CObj_UI::Render(hDC);
}

void CUI_Depot_Wire::Release()
{
}

UIOBJECTTYPE CUI_Depot_Wire::GetType() const
{
    return UI_OBJECT_WIRE;
}

int CUI_Depot_Wire::GetDetailType() const
{
    return WIRE_DEPOT_BIG;
}

void CUI_Depot_Wire::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Wire/Large/Depot/Depot_Big_Wire.bmp", L"Depot_Big_Wire");
}
