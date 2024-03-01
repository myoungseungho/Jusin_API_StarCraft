#include "stdafx.h"
#include "UI_Medic_Icon.h"
#include "BmpMgr.h"

CUI_Medic_Icon::CUI_Medic_Icon()
{
	InsertBmpFile();
}

CUI_Medic_Icon::~CUI_Medic_Icon()
{
	Release();
}

void CUI_Medic_Icon::Initialize()
{
	//처음 크기 고정
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	__super::Update_Rect();


	m_pFrameKey = L"MEDIC_ICON";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_UI;
}

int CUI_Medic_Icon::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	return 0;
}

void CUI_Medic_Icon::Late_Update()
{
}

void CUI_Medic_Icon::Render(HDC hDC)
{
	CObj_UI::Render(hDC);
}

void CUI_Medic_Icon::Release()
{
}

void CUI_Medic_Icon::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CmdIcon/Builduse/MEDIC_ICON.bmp", L"MEDIC_ICON");
}

UIOBJECTTYPE CUI_Medic_Icon::GetType() const
{
	return UI_OBJECT_ICON;
}

int CUI_Medic_Icon::GetDetailType() const
{
	return ICON_MEDIC;
}
