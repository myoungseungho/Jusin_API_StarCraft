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
	m_pFrameKey = L"Attack_Image";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();
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
}

void CUI_Attack_Icon::Release()
{
}

void CUI_Attack_Icon::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CmdIcon/Unituse/Attack_Image.bmp", L"Attack_Image");
}
