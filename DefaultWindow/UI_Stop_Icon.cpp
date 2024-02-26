#include "stdafx.h"
#include "UI_Stop_Icon.h"
#include "BmpMgr.h"
CUI_Stop_Icon::CUI_Stop_Icon()
{
	InsertBmpFile();
}

CUI_Stop_Icon::~CUI_Stop_Icon()
{
	Release();
}

void CUI_Stop_Icon::Initialize()
{
	//처음 크기 고정
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	__super::Update_Rect();

	m_pFrameKey = L"Stop_Image";
	m_tFrame.iFrameStart = 1;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_UI;
}

int CUI_Stop_Icon::Update()
{
	return 0;
}

void CUI_Stop_Icon::Late_Update()
{
}

void CUI_Stop_Icon::Render(HDC hDC)
{
}

void CUI_Stop_Icon::Release()
{
}

void CUI_Stop_Icon::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CmdIcon/Unituse/Stop_Image.bmp", L"Stop_Image");
}
