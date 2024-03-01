#include "stdafx.h"
#include "UI_Marine_Wire_Big.h"
#include "BmpMgr.h"
CUI_Marine_Wire_Big::CUI_Marine_Wire_Big()
{
    InsertBmpFile();
}

CUI_Marine_Wire_Big::~CUI_Marine_Wire_Big()
{
    Release();
}

void CUI_Marine_Wire_Big::Initialize()
{
	//처음 크기 고정
	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 64.f;
	__super::Update_Rect();

	m_pFrameKey = L"Marine_Big_Wire";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_UI;
}

int CUI_Marine_Wire_Big::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	return 0;
}

void CUI_Marine_Wire_Big::Late_Update()
{
}

void CUI_Marine_Wire_Big::Render(HDC hDC)
{
	CObj_UI::Render(hDC);
}

void CUI_Marine_Wire_Big::Release()
{
}

void CUI_Marine_Wire_Big::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Wire/Large/Marine/Marine_Big_Wire.bmp", L"Marine_Big_Wire");
}

UIOBJECTTYPE CUI_Marine_Wire_Big::GetType() const
{
    return UI_OBJECT_WIRE;
}

int CUI_Marine_Wire_Big::GetDetailType() const
{
    return WIRE_MARINE_BIG;
}
