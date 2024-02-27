#include "stdafx.h"
#include "LClick_Mouse.h"
#include "ScrollMgr.h"
#include "Obj.h"
#include "ObjMgr.h"
#include "UnitControlMgr.h"
#include "KeyMgr.h"
#include "UIMgr.h"
#include "Obj_Static.h"
#include "TileMgr.h"
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


	// UI창에 입력이 되었다면
	if (Pt.y > 450.f)
	{
		//좌표에 해당하는 아이콘 반환
		CObj* target = CObjMgr::Get_Instance()->Get_Target_UI(Pt.x, Pt.y);
		if (target != nullptr)
		{
			CUIMgr::Get_Instance()->Set_SCV_UI(target);
		}
	}
	else
	{
		Pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		Pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		//좌표에 해당하는 유닛을 반환한다.
		CObj* target = CObjMgr::Get_Instance()->Get_Target(Pt.x, Pt.y);
		//유닛만 해당
		CObj_Dynamic* dynamicObj = dynamic_cast<CObj_Dynamic*>(target);

		if (target != nullptr && dynamicObj)
		{
			//오브젝트가 이미 선택되었다면
			if (bHasSelect)
				CUnitControlMgr::Get_Instance()->Set_Clear_Unit();

			CUIMgr::Get_Instance()->SetUI(target);

			//선택된 유닛이 다이나믹 오브젝트라면
			CObj_Dynamic* dynamicObj = dynamic_cast<CObj_Dynamic*>(target);
			if (dynamicObj != nullptr)
			{
				CUnitControlMgr::Get_Instance()->Set_Add_Unit(target);
				CKeyMgr::Get_Instance()->Set_bSelectUnit(true);
				dynamic_cast<CObj_Dynamic*>(target)->ChangeState(IDLE_STATE);
			}
			else
			{
				//선택된 유닛이 스태틱 오브젝트라면
				CObj_Static* staticObj = dynamic_cast<CObj_Static*>(target);
				if (staticObj != nullptr)
				{

				}
			}
		}
		else if (target == nullptr)
		{
			UI_BUILDINGSTATE BuildingState = CUIMgr::Get_Instance()->GetBuilding();
			if (BuildingState != UI_STATIC_OBJ_END)
			{
				//SCV가 이제 해당 위치까지 가야함
				vector<CObj_Dynamic*> vecUnit = CUnitControlMgr::Get_Instance()->GetVecUnit();
				if (vecUnit.size() >= 1)
				{
					POINT	Pt;
					GetCursorPos(&Pt);
					ScreenToClient(g_hWnd, &Pt);

					Pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
					Pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

					CObj_Dynamic* target = vecUnit.back();

					target->ChangeStateWithMouse(Pt, BUILD_STATE);
					CUIMgr::Get_Instance()->SetClear_StaticObj();
					CKeyMgr::Get_Instance()->Set_bSelectUnit(false);
					CUnitControlMgr::Get_Instance()->Set_Clear_Unit();
				}
			}
			else
			{
				CUIMgr::Get_Instance()->SetClear_IconObj();
				CUnitControlMgr::Get_Instance()->Set_Clear_Unit();
				CKeyMgr::Get_Instance()->Set_bSelectUnit(false);
			}
		}
	}
}
