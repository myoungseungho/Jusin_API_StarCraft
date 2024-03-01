#include "stdafx.h"
#include "UI_Factory_Wire.h"
#include "BmpMgr.h"

CUI_Factory_Wire::CUI_Factory_Wire()
{
    InsertBmpFile();
}

CUI_Factory_Wire::~CUI_Factory_Wire()
{
    Release();
}

void CUI_Factory_Wire::Initialize()
{	
	//처음 크기 고정
	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 64.f;
	__super::Update_Rect();

	m_pFrameKey = L"Factory_Big_Wire";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_UI;
}

int CUI_Factory_Wire::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	return 0;
}

void CUI_Factory_Wire::Late_Update()
{
}

void CUI_Factory_Wire::Render(HDC hDC)
{
	CObj_UI::Render(hDC);
}

void CUI_Factory_Wire::Release()
{
}

UIOBJECTTYPE CUI_Factory_Wire::GetType() const
{
	return UI_OBJECT_WIRE;
}

int CUI_Factory_Wire::GetDetailType() const
{
	return WIRE_FACTORY_BIG;
}

void CUI_Factory_Wire::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Wire/Large/Factory/Factory_Big_Wire.bmp", L"Factory_Big_Wire");
}
