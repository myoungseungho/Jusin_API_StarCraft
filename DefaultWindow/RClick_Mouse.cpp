#include "stdafx.h"
#include "RClick_Mouse.h"
#include "ScrollMgr.h"
#include "Obj.h"
#include "ObjMgr.h"
#include "UnitControlMgr.h"
#include "KeyMgr.h"
#include "Scv.h"
#include "Obj_Static.h"
#include "Tank.h"
CRClick_Mouse::CRClick_Mouse()
{
}

CRClick_Mouse::~CRClick_Mouse()
{
}

void CRClick_Mouse::RClick()
{

}

void CRClick_Mouse::Release()
{
}

void CRClick_Mouse::Initialize()
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

	//좌표에 해당하는 유닛을 반환한다.
	CObj* target = CObjMgr::Get_Instance()->Get_Target(Pt.x, Pt.y);


	vector<CObj*> vecUnit = CUnitControlMgr::Get_Instance()->GetVecUnitOrBuilding();

	//선택된 유닛중에서 타겟이 있고, 타겟이 적이라면 공격, 아니면 이동
	for (auto iter : vecUnit)
	{
		//건물이면 Return
		if (dynamic_cast<CObj_Static*>(iter) != nullptr)
			return;

		CObj_Dynamic* dynamicIter = dynamic_cast<CObj_Dynamic*>(iter);

		if (dynamicIter)
		{
			CTank* tank = dynamic_cast<CTank*>(iter);
			if (tank)
			{
				if (tank->GetStateID() == SIEGEMODE_STATE)
					return;
			}

			CScv* scv = dynamic_cast<CScv*>(iter);
			if (scv != nullptr && scv->GetStateID() == BUILD_STATE)
				return;

			if (target != nullptr)
			{
				FACTIONSTATE factionId = target->Get_FactionState();

				switch (factionId)
				{
				case FACTION_NON:
					dynamicIter->ChangeStateWithMouse(Pt, WALK_STATE);
					break;
				case FACTION_ALLY:
					dynamicIter->ChangeStateWithMouse(Pt, WALK_STATE);
					break;
				case FACTION_ENEMY:
					dynamicIter->ChangeStateWithMouse(Pt, WALK_STATE);
					break;
				case FACTION_RESOURCE:
					if (scv != nullptr)
						dynamicIter->ChangeStateWithMouse(Pt, COLLECTION_STATE);
					else
						dynamicIter->ChangeStateWithMouse(Pt, WALK_STATE);
					break;
				case FACTION_END:
					break;
				default:
					break;
				}
			}
			else
			{
				dynamicIter->ChangeStateWithMouse(Pt, WALK_STATE);

			}
		}
	}
}
