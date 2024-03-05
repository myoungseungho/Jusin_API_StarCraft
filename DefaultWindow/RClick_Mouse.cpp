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

	//���� �̵�
	POINT	Pt;
	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	Pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	Pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//���콺 â ������ ������
	if (Pt.x<0 || Pt.x>MAPCX || Pt.y<0 || Pt.y>MAPCY)
		return;

	//��ǥ�� �ش��ϴ� ������ ��ȯ�Ѵ�.
	CObj* target = CObjMgr::Get_Instance()->Get_Target(Pt.x, Pt.y);


	vector<CObj*> vecUnit = CUnitControlMgr::Get_Instance()->GetVecUnitOrBuilding();

	//���õ� �����߿��� Ÿ���� �ְ�, Ÿ���� ���̶�� ����, �ƴϸ� �̵�
	for (auto iter : vecUnit)
	{
		//�ǹ��̸� Return
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
