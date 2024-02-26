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

	//��ǥ�� �ش��ϴ� ������ ��ȯ�Ѵ�.
	CObj* target = CObjMgr::Get_Instance()->Get_Target(Pt.x, Pt.y);

	if (target != nullptr)
	{
		//������Ʈ�� �̹� ���õǾ��ٸ�
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
