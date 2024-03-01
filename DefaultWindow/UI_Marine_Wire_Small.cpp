#include "stdafx.h"
#include "UI_Marine_Wire_Small.h"
#include "BmpMgr.h"
CUI_Marine_Wire_Small::CUI_Marine_Wire_Small()
{
    InsertBmpFile();
}

CUI_Marine_Wire_Small::~CUI_Marine_Wire_Small()
{
    Release();
}

void CUI_Marine_Wire_Small::Initialize()
{
	//처음 크기 고정
	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;
	__super::Update_Rect();

	m_pFrameKey = L"Marine_Small_Wire";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_UI;
}

int CUI_Marine_Wire_Small::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	return 0;
}

void CUI_Marine_Wire_Small::Late_Update()
{
}

void CUI_Marine_Wire_Small::Render(HDC hDC)
{
	CObj_UI::Render(hDC);
}

void CUI_Marine_Wire_Small::Release()
{
}

UIOBJECTTYPE CUI_Marine_Wire_Small::GetType() const
{
    return UI_OBJECT_WIRE;
}

int CUI_Marine_Wire_Small::GetDetailType() const
{
    return WIRE_MARINE_SMALL;
}

void CUI_Marine_Wire_Small::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Wire/Small/Marine/Marine_Small_Wire.bmp", L"Marine_Small_Wire");
}
