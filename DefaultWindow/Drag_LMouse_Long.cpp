#include "stdafx.h"
#include "Drag_LMouse_Long.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "ObjMgr.h"
#include "UnitControlMgr.h"
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
	UpdatePT();

	// 드래그 LEFT,TOP과 RIGHT, DOWN 사이에 들어간 유닛을 셋팅해야 함.
	vector<CObj*> vecTargets = CObjMgr::Get_Instance()->Get_Targets(m_InitPoint, m_CurrentPoint);
	CUnitControlMgr::Get_Instance()->Set_Add_Unit(vecTargets);
}

void Drag_LMouse_Long::UpdatePT()
{
	//유닛 이동
	POINT	Pt;
	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	Pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	Pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	m_CurrentPoint = Pt;
}

void Drag_LMouse_Long::Release()
{
}

