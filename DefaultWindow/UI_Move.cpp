#include "stdafx.h"
#include "UI_Move.h"
#include "BmpMgr.h"
CUI_Move_Icon::CUI_Move_Icon()
{
	InsertBmpFile();
}

CUI_Move_Icon::~CUI_Move_Icon()
{
	Release();
}

void CUI_Move_Icon::Initialize()
{
	//처음 크기 고정
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	__super::Update_Rect();

	m_pFrameKey = L"Move_Image";
	m_tFrame.iFrameStart = 1;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_UI;
}

int CUI_Move_Icon::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	return 0;
}

void CUI_Move_Icon::Late_Update()
{
}

void CUI_Move_Icon::Render(HDC hDC)
{
	CObj_UI::Render(hDC);
}

void CUI_Move_Icon::Release()
{
}

void CUI_Move_Icon::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CmdIcon/Unituse/Move_Image.bmp", L"Move_Image");
}

UIOBJECTTYPE CUI_Move_Icon::GetType() const
{
	return UI_OBJECT_ICON;
}

int CUI_Move_Icon::GetDetailType() const
{
	return ICON_MOVE;
}
