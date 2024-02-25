#include "stdafx.h"
#include "RClick_Mouse.h"
#include "ScrollMgr.h"
#include "Obj.h"
#include "ObjMgr.h"
#include "UnitControlMgr.h"
#include "KeyMgr.h"
CRClick_Mouse::CRClick_Mouse()
{
}

CRClick_Mouse::~CRClick_Mouse()
{
}

void CRClick_Mouse::RClick()
{
	bool bHasSelectUnit = CKeyMgr::Get_Instance()->Get_bSelectUnit();

	if (!bHasSelectUnit)
		return;

	//유닛 이동
	POINT	Pt;
	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	Pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	Pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//마우스 창 밖으로 나가면
	if (Pt.x<0 || Pt.x>MAPCX || Pt.y<0 || Pt.y>MAPCY)
		return;


	vector<CObj_Dynamic*> vecUnit = CUnitControlMgr::Get_Instance()->GetVecUnit();

	for (auto& iter : vecUnit)
	{
		iter->ChangeStateWithMouse(Pt, WALK_STATE);
	}
}
