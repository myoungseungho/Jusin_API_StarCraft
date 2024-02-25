#include "stdafx.h"
#include "Drag_LMouse_Long.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "ObjMgr.h"
#include "UnitControlMgr.h"
#include "KeyMgr.h"
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
}

void Drag_LMouse_Long::UpdatePT()
{
	//���� �̵�
	POINT	Pt;
	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	Pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	Pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	m_CurrentPoint = Pt;
}

void Drag_LMouse_Long::Release()
{
	// �巡�� LEFT,TOP�� RIGHT, DOWN ���̿� �� ������ �����ؾ� ��.
	vector<CObj*> vecTargets = CObjMgr::Get_Instance()->Get_Targets(m_InitPoint, m_CurrentPoint);

	if (vecTargets.size() != 0)
	{
		CUnitControlMgr::Get_Instance()->Set_Add_Unit(vecTargets);
		CKeyMgr::Get_Instance()->Set_bSelectUnit(true);
	}
	else
	{
		CKeyMgr::Get_Instance()->Set_bSelectUnit(false);
	}
}

