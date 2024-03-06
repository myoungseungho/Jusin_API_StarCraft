#include "stdafx.h"
#include "UI_Academy_Wire.h"
#include "BmpMgr.h"

CUI_Academy_Wire::CUI_Academy_Wire()
{
    InsertBmpFile();
}

CUI_Academy_Wire::~CUI_Academy_Wire()
{
    Release();
}

void CUI_Academy_Wire::Initialize()
{
	//처음 크기 고정
	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 64.f;
	__super::Update_Rect();

	m_pFrameKey = L"Academy_Big_Wire";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_UI;
}

int CUI_Academy_Wire::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	return 0;
}

void CUI_Academy_Wire::Late_Update()
{
}

void CUI_Academy_Wire::Render(HDC hDC)
{
	CObj_UI::Render(hDC);
}

void CUI_Academy_Wire::Release()
{
}

UIOBJECTTYPE CUI_Academy_Wire::GetType() const
{
	return UI_OBJECT_WIRE;
}

int CUI_Academy_Wire::GetDetailType() const
{
	return WIRE_ACADEMY_BIG;
}

void CUI_Academy_Wire::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Wire/Large/Academy/Academy_Big_Wire.bmp", L"Academy_Big_Wire");
}