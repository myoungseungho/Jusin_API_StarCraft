#include "stdafx.h"
#include "UI_Barrack.h"
#include "BmpMgr.h"

CUI_Barrack_Icon::CUI_Barrack_Icon()
{
	InsertBmpFile();
}

CUI_Barrack_Icon::~CUI_Barrack_Icon()
{
	Release();
}

void CUI_Barrack_Icon::Initialize()
{
	m_pFrameKey = L"Barrack_Icon";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();
}

int CUI_Barrack_Icon::Update()
{
    return 0;
}

void CUI_Barrack_Icon::Late_Update()
{
}

void CUI_Barrack_Icon::Render(HDC hDC)
{
}

void CUI_Barrack_Icon::Release()
{
}

void CUI_Barrack_Icon::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CmdIcon/BasicBuilding/Barrack_Icon.bmp", L"Barrack_Icon");
}
