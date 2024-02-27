#include "stdafx.h"
#include "UI_Tank_Icon.h"
#include "BmpMgr.h"

CUI_Tank_Icon::CUI_Tank_Icon()
{
	InsertBmpFile();
}

CUI_Tank_Icon::~CUI_Tank_Icon()
{
	Release();
}

void CUI_Tank_Icon::Initialize()
{
	//처음 크기 고정
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	__super::Update_Rect();


	m_pFrameKey = L"TANK_ICON";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_UI;
}

int CUI_Tank_Icon::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	return 0;
}

void CUI_Tank_Icon::Late_Update()
{
}

void CUI_Tank_Icon::Render(HDC hDC)
{
	CObj_UI::Render(hDC);
}

void CUI_Tank_Icon::Release()
{
}

void CUI_Tank_Icon::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CmdIcon/Builduse/TANK_ICON.bmp", L"TANK_ICON");
}

ICONSTATE CUI_Tank_Icon::GetType() const
{
	return ICON_TANK;
}
