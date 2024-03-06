#include "stdafx.h"
#include "UI_Science_Facility_Wire.h"
#include "BmpMgr.h"

CUI_Science_Facility_Wire::CUI_Science_Facility_Wire()
{
    InsertBmpFile();
}

CUI_Science_Facility_Wire::~CUI_Science_Facility_Wire()
{
    Release();
}

void CUI_Science_Facility_Wire::Initialize()
{
	//처음 크기 고정
	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 64.f;
	__super::Update_Rect();

	m_pFrameKey = L"Reserch_Big_Wire";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_UI;
}

int CUI_Science_Facility_Wire::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	return 0;
}

void CUI_Science_Facility_Wire::Late_Update()
{
}

void CUI_Science_Facility_Wire::Render(HDC hDC)
{
	CObj_UI::Render(hDC);
}

void CUI_Science_Facility_Wire::Release()
{
}

UIOBJECTTYPE CUI_Science_Facility_Wire::GetType() const
{
	return UI_OBJECT_WIRE;
}

int CUI_Science_Facility_Wire::GetDetailType() const
{
	return WIRE_SCIENCE_FACILITY;
}

void CUI_Science_Facility_Wire::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Wire/Large/Reserch/Reserch_Big_Wire.bmp", L"Reserch_Big_Wire");
}
