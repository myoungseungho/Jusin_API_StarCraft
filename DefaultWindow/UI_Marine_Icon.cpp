#include "stdafx.h"
#include "UI_Marine_Icon.h"
#include "BmpMgr.h"

CUI_Marine_Icon::CUI_Marine_Icon()
{
    InsertBmpFile();
}

CUI_Marine_Icon::~CUI_Marine_Icon()
{
    Release();
}

void CUI_Marine_Icon::Initialize()
{
	//처음 크기 고정
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	__super::Update_Rect();


	m_pFrameKey = L"Center_Icon";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_UI;
}

int CUI_Marine_Icon::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	return 0;
}

void CUI_Marine_Icon::Late_Update()
{
}

void CUI_Marine_Icon::Render(HDC hDC)
{
}

void CUI_Marine_Icon::Release()
{
}

void CUI_Marine_Icon::InsertBmpFile()
{
}

ICONSTATE CUI_Marine_Icon::GetType() const
{
	return ICON_MARINE;
}
