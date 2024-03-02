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
	//처음 크기 고정
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	__super::Update_Rect();

	m_pFrameKey = L"Barrack_Icon";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_UI;
}

int CUI_Barrack_Icon::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
    return 0;
}

void CUI_Barrack_Icon::Late_Update()
{
}

void CUI_Barrack_Icon::Render(HDC hDC)
{
	GdiTransparentBlt(
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		m_tRect.left,	// 복사 받을 이미지의 가로, 세로
		m_tRect.top,
		(int)m_tInfo.fCX,	// 복사 받을 이미지의 가로, 세로
		(int)m_tInfo.fCY,
		Get_HDC(),		// 비트맵을 가지고 있는 DC
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,			// 비트맵 출력 시작 좌표 LEFT, TOP
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,	// 출력할 비트맵 가로
		(int)m_tInfo.fCY,	// 출력할 비트맵 세로
		RGB(0, 0, 0));	// 제거할 색상 값
}

void CUI_Barrack_Icon::Release()
{
}

void CUI_Barrack_Icon::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CmdIcon/BasicBuilding/Barrack_Icon.bmp", L"Barrack_Icon");
}

UIOBJECTTYPE CUI_Barrack_Icon::GetType() const
{
	return UI_OBJECT_ICON;
}

int CUI_Barrack_Icon::GetDetailType() const
{
	return ICON_BARRACK;
}

