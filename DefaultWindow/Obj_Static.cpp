#include "stdafx.h"
#include "Obj_Static.h"
#include "TileMgr.h"
#include "ScrollMgr.h"
CObj_Static::CObj_Static() : m_UIBuilding(false), m_CompleteBuilding(false)
{
}

CObj_Static::~CObj_Static()
{
}


void CObj_Static::Spawn_Unit(DYNAMIC_OBJID)
{
}

void CObj_Static::Move_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			m_CompleteBuilding = true;
			m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
		}

		m_tFrame.dwTime = GetTickCount();
	}
}

void CObj_Static::SetObstcale()
{
	CTileMgr::Get_Instance()->SetStaticObstcales(this);
}

void CObj_Static::UIBuilding()
{
	POINT	Pt;
	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	Pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	Pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	m_tInfo.fX = Pt.x;
	m_tInfo.fY = Pt.y;
}



