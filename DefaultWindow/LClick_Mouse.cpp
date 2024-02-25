#include "stdafx.h"
#include "LClick_Mouse.h"
#include "ScrollMgr.h"
#include "Obj.h"
#include "ObjMgr.h"
#include "UnitControlMgr.h"
#include "KeyMgr.h"
CLClick_Mouse::CLClick_Mouse()
{
}

CLClick_Mouse::~CLClick_Mouse()
{
}

void CLClick_Mouse::LClick()
{
	POINT	Pt;
	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);
	bool bHasSelectUnit = CKeyMgr::Get_Instance()->Get_bSelectUnit();
	Pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	Pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	int	TileX = Pt.x / TILECX;
	int	TileY = Pt.y / TILECY;

	//좌표에 해당하는 유닛을 반환한다.
	CObj* target = CObjMgr::Get_Instance()->Get_Target(Pt.x, Pt.y);

	if (target != nullptr)
	{
		//이미 유닛이 한마리 선택되었다면
		if (bHasSelectUnit)
		{
			CUnitControlMgr::Get_Instance()->Set_Clear_Unit();
		}

		CObj_Dynamic* dynamicObj = dynamic_cast<CObj_Dynamic*>(target);

		if (dynamicObj != nullptr)
		{
			CKeyMgr::Get_Instance()->Set_bSelectUnit(true);
			CUnitControlMgr::Get_Instance()->Set_Add_Unit(dynamicObj);
		}
	}
	else
	{
		CUnitControlMgr::Get_Instance()->Set_Clear_Unit();
		CKeyMgr::Get_Instance()->Set_bSelectUnit(false);
	}
}

void CLClick_Mouse::Initialize()
{
}
