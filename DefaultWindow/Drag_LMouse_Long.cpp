#include "stdafx.h"
#include "Drag_LMouse_Long.h"
#include "ScrollMgr.h"

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


void Drag_LMouse_Long::DragLClick()
{
	//À¯´Ö ÀÌµ¿
	POINT	Pt;
	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	Pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	Pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();
}

