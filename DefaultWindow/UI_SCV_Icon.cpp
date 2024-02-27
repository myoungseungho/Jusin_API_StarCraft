#include "stdafx.h"
#include "UI_SCV_Icon.h"
#include "BmpMgr.h"

CUI_SCV_Icon::CUI_SCV_Icon()
{
    InsertBmpFile();
}

CUI_SCV_Icon::~CUI_SCV_Icon()
{
    Release();
}

void CUI_SCV_Icon::Initialize()
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

int CUI_SCV_Icon::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	return 0;
}

void CUI_SCV_Icon::Late_Update()
{
}

void CUI_SCV_Icon::Render(HDC hDC)
{
	CObj_UI::Render(hDC);
}

void CUI_SCV_Icon::Release()
{
}

void CUI_SCV_Icon::InsertBmpFile()
{
}

ICONSTATE CUI_SCV_Icon::GetType() const
{
	return ICON_SCV;
}
