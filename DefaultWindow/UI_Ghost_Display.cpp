#include "stdafx.h"
#include "UI_Ghost_Display.h"
#include "BmpMgr.h"

CUI_Ghost_Display::CUI_Ghost_Display()
{
}

CUI_Ghost_Display::~CUI_Ghost_Display()
{
}

void CUI_Ghost_Display::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Ghost_Display.bmp", L"Ghost_Display");

	m_eRender = RENDER_UI;

	m_pFrameKey = L"Ghost_Display";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 59;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100.f;
	m_tFrame.dwTime = GetTickCount();
}

int CUI_Ghost_Display::Update()
{
	return 0;
}

void CUI_Ghost_Display::Late_Update()
{
	Move_Frame();
}

void CUI_Ghost_Display::Render(HDC hDC)
{
	HDC	hSelectDisplay = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	GdiTransparentBlt(
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		523, // 복사 받을 위치 좌표
		517,
		60,	// 복사 받을 이미지의 가로, 세로
		56,
		hSelectDisplay,		// 비트맵을 가지고 있는 DC
		60 * m_tFrame.iFrameStart,			// 비트맵 출력 시작 좌표 LEFT, TOP
		56 * m_tFrame.iMotion,
		60,	// 출력할 비트맵 가로
		56,	// 출력할 비트맵 세로
		RGB(0, 0, 0));	// 제거할 색상 값
}

void CUI_Ghost_Display::Release()
{
}

UIOBJECTTYPE CUI_Ghost_Display::GetType() const
{
	return UI_OBJECT_DISPLAY;
}

int CUI_Ghost_Display::GetDetailType() const
{
	return 0;
}
