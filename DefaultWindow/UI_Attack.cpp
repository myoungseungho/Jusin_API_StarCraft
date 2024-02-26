#include "stdafx.h"
#include "UI_Attack.h"
#include "BmpMgr.h"
CUI_Attack_Icon::CUI_Attack_Icon()
{
	InsertBmpFile();
}

CUI_Attack_Icon::~CUI_Attack_Icon()
{
	Release();
}

void CUI_Attack_Icon::Initialize()
{
	//처음 크기 고정
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	__super::Update_Rect();

	m_pFrameKey = L"Attack_Image";
	m_tFrame.iFrameStart = 1;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_UI;
}

int CUI_Attack_Icon::Update()
{
    return 0;
}

void CUI_Attack_Icon::Late_Update()
{
}

void CUI_Attack_Icon::Render(HDC hDC)
{
	CObj_UI::Render(hDC);
}

void CUI_Attack_Icon::Release()
{
}

void CUI_Attack_Icon::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CmdIcon/Unituse/Attack_Image.bmp", L"Attack_Image");
}
