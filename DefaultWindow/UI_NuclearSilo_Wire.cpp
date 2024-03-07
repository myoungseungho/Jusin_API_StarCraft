#include "stdafx.h"
#include "UI_NuclearSilo_Wire.h"
#include "BmpMgr.h"

CUI_NuclearSilo_Wire::CUI_NuclearSilo_Wire()
{
    InsertBmpFile();
}

CUI_NuclearSilo_Wire::~CUI_NuclearSilo_Wire()
{
    Release();
}

void CUI_NuclearSilo_Wire::Initialize()
{
	//처음 크기 고정
	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 64.f;
	__super::Update_Rect();

	m_pFrameKey = L"NuclearSilo_Wire";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_UI;
}

int CUI_NuclearSilo_Wire::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	return 0;
}

void CUI_NuclearSilo_Wire::Late_Update()
{
}

void CUI_NuclearSilo_Wire::Render(HDC hDC)
{
	CObj_UI::Render(hDC);
}

void CUI_NuclearSilo_Wire::Release()
{
}

UIOBJECTTYPE CUI_NuclearSilo_Wire::GetType() const
{
	return UI_OBJECT_WIRE;
}

int CUI_NuclearSilo_Wire::GetDetailType() const
{
	return WIRE_NUKELSILO_BIG;
}

void CUI_NuclearSilo_Wire::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Wire/Large/Nukelsilo/NuclearSilo_Wire.bmp", L"NuclearSilo_Wire");
}
