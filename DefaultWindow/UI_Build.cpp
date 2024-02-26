#include "stdafx.h"
#include "UI_Build.h"
#include "BmpMgr.h"
CUI_Build_Icon::CUI_Build_Icon()
{
	InsertBmpFile();
}

CUI_Build_Icon::~CUI_Build_Icon()
{
	Release();
}

void CUI_Build_Icon::Initialize()
{
	m_pFrameKey = L"Build_Image";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();
}

int CUI_Build_Icon::Update()
{
	return 0;
}

void CUI_Build_Icon::Late_Update()
{
}

void CUI_Build_Icon::Render(HDC hDC)
{
}

void CUI_Build_Icon::Release()
{
}

void CUI_Build_Icon::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CmdIcon/Unituse/Build_Image.bmp", L"Build_Image");
}
