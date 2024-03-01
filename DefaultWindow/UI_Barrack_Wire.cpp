#include "stdafx.h"
#include "UI_Barrack_Wire.h"
#include "BmpMgr.h"

CUI_Barrack_Wire::CUI_Barrack_Wire()
{
	InsertBmpFile();
}

CUI_Barrack_Wire::~CUI_Barrack_Wire()
{
	Release();
}

void CUI_Barrack_Wire::Initialize()
{
	//처음 크기 고정
	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 64.f;
	__super::Update_Rect();

	m_pFrameKey = L"Barrack_Big_Wire";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_UI;
}

int CUI_Barrack_Wire::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	return 0;
}

void CUI_Barrack_Wire::Late_Update()
{
}

void CUI_Barrack_Wire::Render(HDC hDC)
{
	CObj_UI::Render(hDC);
}

void CUI_Barrack_Wire::Release()
{
}

UIOBJECTTYPE CUI_Barrack_Wire::GetType() const
{
	return UI_OBJECT_WIRE;
}

int CUI_Barrack_Wire::GetDetailType() const
{
	return WIRE_BARRACK_BIG;
}

void CUI_Barrack_Wire::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Wire/Large/Barrack/Barrack_Big_Wire.bmp", L"Barrack_Big_Wire");
}
