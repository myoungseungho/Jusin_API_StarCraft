#include "stdafx.h"
#include "UI_Advanced_Build.h"
#include "BmpMgr.h"
CUI_Advanced_Build_Icon::CUI_Advanced_Build_Icon()
{
	InsertBmpFile();
}

CUI_Advanced_Build_Icon::~CUI_Advanced_Build_Icon()
{
	Release();
}

void CUI_Advanced_Build_Icon::Initialize()
{
	m_pFrameKey = L"Advanced_Image";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();
}

int CUI_Advanced_Build_Icon::Update()
{
	return 0;
}

void CUI_Advanced_Build_Icon::Late_Update()
{
}

void CUI_Advanced_Build_Icon::Render(HDC hDC)
{
}

void CUI_Advanced_Build_Icon::Release()
{
}

void CUI_Advanced_Build_Icon::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CmdIcon/Unituse/Advanced_Image.bmp", L"Advanced_Image");
}
