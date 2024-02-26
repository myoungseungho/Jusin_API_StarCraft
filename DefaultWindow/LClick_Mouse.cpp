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

}

void CLClick_Mouse::Release()
{
}

void CLClick_Mouse::Initialize()
{
	POINT	Pt;
	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);
	bool bHasSelect = CKeyMgr::Get_Instance()->Get_bSelectUnit();
	Pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	Pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//int	TileX = Pt.x / TILECX;
	//int	TileY = Pt.y / TILECY;

	//좌표에 해당하는 유닛을 반환한다.
	CObj* target = CObjMgr::Get_Instance()->Get_Target(Pt.x, Pt.y);

	if (target != nullptr)
	{
		//오브젝트가 이미 선택되었다면
		if (bHasSelect)
			CUnitControlMgr::Get_Instance()->Set_Clear_Unit();

		CUnitControlMgr::Get_Instance()->Set_Add_Unit(target);
		CKeyMgr::Get_Instance()->Set_bSelectUnit(true);
	}
	else
	{
		CUnitControlMgr::Get_Instance()->Set_Clear_Unit();
		CKeyMgr::Get_Instance()->Set_bSelectUnit(false);
	}
}
