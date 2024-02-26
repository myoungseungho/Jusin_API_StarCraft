#include "stdafx.h"
#include "RClick_Mouse.h"
#include "ScrollMgr.h"
#include "Obj.h"
#include "ObjMgr.h"
#include "UnitControlMgr.h"
#include "KeyMgr.h"
#include "Scv.h"
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

	vector<CObj_Dynamic*> vecUnit = CUnitControlMgr::Get_Instance()->GetVecUnit();

	//���õ� �����߿��� Ÿ���� �ְ�, Ÿ���� ���̶�� ����, �ƴϸ� �̵�
	for (auto& iter : vecUnit)
	{
		if (target != nullptr)
		{
			FACTIONSTATE factionId = target->Get_FactionState();
			CScv* scv = dynamic_cast<CScv*>(target);

			switch (factionId)
			{
			case FACTION_NON:
				iter->ChangeStateWithMouse(Pt, WALK_STATE);
				break;
			case FACTION_ALLY:
				iter->ChangeStateWithMouse(Pt, WALK_STATE);
				break;
			case FACTION_ENEMY:
				iter->ChangeStateWithMouse(Pt, ATTACK_STATE);
				break;
			case FACTION_RESOURCE:
				if (scv != nullptr)
					iter->ChangeStateWithMouse(Pt, ATTACK_STATE);
				else
					iter->ChangeStateWithMouse(Pt, WALK_STATE);
				break;
			case FACTION_END:
				break;
			default:
				break;
			}
		}
		else
		{
			iter->ChangeStateWithMouse(Pt, WALK_STATE);
		}
	}
}
