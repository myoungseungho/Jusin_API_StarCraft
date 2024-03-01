#include "stdafx.h"
#include "UI_Center_Wire.h"
#include "BmpMgr.h"

CUI_Center_Wire::CUI_Center_Wire()
{
	InsertBmpFile();
}

CUI_Center_Wire::~CUI_Center_Wire()
{
	Release();
}

void CUI_Center_Wire::Initialize()
{
	//처음 크기 고정
	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 64.f;
	__super::Update_Rect();

	m_pFrameKey = L"Center_Big_Wire";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_UI;
}

int CUI_Center_Wire::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	return 0;
}

void CUI_Center_Wire::Late_Update()
{
}

void CUI_Center_Wire::Render(HDC hDC)
{
	CObj_UI::Render(hDC);
}

void CUI_Center_Wire::Release()
{
}

UIOBJECTTYPE CUI_Center_Wire::GetType() const
{
	return UI_OBJECT_WIRE;
}

int CUI_Center_Wire::GetDetailType() const
{
	return WIRE_CENTER_BIG;
}

void CUI_Center_Wire::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Wire/Large/Control/Center_Big_Wire.bmp", L"Center_Big_Wire");
}
