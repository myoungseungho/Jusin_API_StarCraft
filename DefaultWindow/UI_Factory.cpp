#include "stdafx.h"
#include "UI_Factory.h"
#include "BmpMgr.h"

CUI_Factory_Icon::CUI_Factory_Icon()
{
	InsertBmpFile();
}

CUI_Factory_Icon::~CUI_Factory_Icon()
{
	Release();
}

void CUI_Factory_Icon::Initialize()
{
	m_pFrameKey = L"Factory_Icon";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();
}

int CUI_Factory_Icon::Update()
{
    return 0;
}

void CUI_Factory_Icon::Late_Update()
{
}

void CUI_Factory_Icon::Render(HDC hDC)
{
}

void CUI_Factory_Icon::Release()
{
}

void CUI_Factory_Icon::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CmdIcon/AdvancedBuilding/Factory_Icon.bmp", L"Factory_Icon");
}
