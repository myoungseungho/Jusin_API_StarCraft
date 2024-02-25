#include "stdafx.h"
#include "Drag_LMouse_Long.h"
#include "ScrollMgr.h"
#include "TileMgr.h"

Drag_LMouse_Long::Drag_LMouse_Long()
{
}

Drag_LMouse_Long::~Drag_LMouse_Long()
{
}

void Drag_LMouse_Long::Initialize()
{

}

void Drag_LMouse_Long::Initialize(POINT _pt)
{
	m_InitPoint = _pt;
}

void Drag_LMouse_Long::Render(HDC _hdc)
{
	Rectangle(_hdc, m_InitPoint.x, m_InitPoint.y, m_CurrentPoint.x, m_CurrentPoint.y);
}


void Drag_LMouse_Long::DragLClick()
{
	//À¯´Ö ÀÌµ¿
	POINT	Pt;
	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	Pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	Pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	m_CurrentPoint = Pt;
}

