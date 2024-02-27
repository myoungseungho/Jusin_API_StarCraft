#include "stdafx.h"
#include "Obj_UI.h"
#include "UIMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
CObj_UI::CObj_UI()
{
}

CObj_UI::~CObj_UI()
{
}

void CObj_UI::Initialize()
{
	__super::Update_Rect();
}

int CObj_UI::Update()
{
	return 0;
}

void CObj_UI::Late_Update()
{
}

void CObj_UI::Render(HDC hDC)
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

void CObj_UI::Release()
{
}

void CObj_UI::UpdateMouse()
{
	POINT	Pt;
	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	Pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	Pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	m_tInfo.fX = Pt.x;
	m_tInfo.fY = Pt.y;
}

void CObj_UI::Move_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;

		m_tFrame.dwTime = GetTickCount();
	}
}


HDC CObj_UI::Get_HDC()
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	return hMemDC;
}
