#include "stdafx.h"
#include "UI_StarPort.h"
#include "BmpMgr.h"

CUI_StarPort_Icon::CUI_StarPort_Icon()
{
	InsertBmpFile();
}

CUI_StarPort_Icon::~CUI_StarPort_Icon()
{
	Release();
}

void CUI_StarPort_Icon::Initialize()
{
	m_pFrameKey = L"StarPort_Icon";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();
}

int CUI_StarPort_Icon::Update()
{
	return 0;
}

void CUI_StarPort_Icon::Late_Update()
{
}

void CUI_StarPort_Icon::Render(HDC hDC)
{
}

void CUI_StarPort_Icon::Release()
{
}

void CUI_StarPort_Icon::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CmdIcon/AdvancedBuilding/StarPort_Icon.bmp", L"StarPort_Icon");
}
