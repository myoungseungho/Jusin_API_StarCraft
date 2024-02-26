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
	m_pFrameKey = L"Move_Image";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();
}

int CUI_Move_Icon::Update()
{
	return 0;
}

void CUI_Move_Icon::Late_Update()
{
}

void CUI_Move_Icon::Render(HDC hDC)
{
}

void CUI_Move_Icon::Release()
{
}

void CUI_Move_Icon::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CmdIcon/Unituse/Move_Image.bmp", L"Move_Image");
}
