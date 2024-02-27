#include "stdafx.h"
#include "Obj_Static.h"
#include "TileMgr.h"
#include "ScrollMgr.h"
CObj_Static::CObj_Static() : m_IsInfoUpdate(false), m_UIBuilding(false)
{
}

CObj_Static::~CObj_Static()
{
}

void CObj_Static::SetObstcale()
{
	//POINT	Pt;
	//GetCursorPos(&Pt);
	//ScreenToClient(g_hWnd, &Pt);

	//Pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//Pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	//
	//this->Set_PosX(Pt.x);
	//this->Set_PosY(Pt.y);

	list<CObj*> staticTileList = CTileMgr::Get_Instance()->GetStaticTile(this);

	for (auto iter : staticTileList)
	{
		CTile* iterTile = dynamic_cast<CTile*>(iter);

		if (iterTile != nullptr)
		{
			iterTile->Set_Value(1, 0);
		}
	}

	CTileMgr::Get_Instance()->SetVecObstcales(staticTileList);
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



