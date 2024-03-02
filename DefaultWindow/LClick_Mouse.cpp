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
#include "SoundMgr.h"
CLClick_Mouse::CLClick_Mouse()
{
}

CLClick_Mouse::~CLClick_Mouse()
{
}

void CLClick_Mouse::LClick()
{

}

void CLClick_Mouse::HandleUIClick(POINT Pt)
{
	//좌표에 해당하는 아이콘 반환
	CObj* target = CObjMgr::Get_Instance()->Get_Target_UI(Pt.x, Pt.y);

	//아이콘이 있다면
	if (target != nullptr)
	{
		CUIMgr::Get_Instance()->OnClickIcon(target);
	}
}

void CLClick_Mouse::HandleDynamicObjectClick(CObj* target)
{
	//오브젝트가 이미 선택되었다면
	if (CKeyMgr::Get_Instance()->Get_bSelectUnit())
		CUnitControlMgr::Get_Instance()->Set_Clear_Unit();

	CUIMgr::Get_Instance()->OnClickObj(target);

	CUnitControlMgr::Get_Instance()->Set_Add_Unit(target);
	CKeyMgr::Get_Instance()->Set_bSelectUnit(true);
	dynamic_cast<CObj_Dynamic*>(target)->ChangeState(IDLE_STATE);
}

void CLClick_Mouse::HandleStaticObjectClick(CObj* target)
{
	if (CKeyMgr::Get_Instance()->Get_bSelectUnit())
	{
		CUnitControlMgr::Get_Instance()->Set_Clear_Unit();
		CUnitControlMgr::Get_Instance()->Set_Clear_Building();
	}

	CUnitControlMgr::Get_Instance()->Set_Add_Building(target);
	CKeyMgr::Get_Instance()->Set_bSelectUnit(false);
	CUIMgr::Get_Instance()->OnClickObj(target);
}

void CLClick_Mouse::HandleNoTargetClick()
{
	UI_BUILDINGSTATE BuildingState = CUIMgr::Get_Instance()->GetBuilding();
	if (BuildingState != UI_STATIC_OBJ_END)
	{
		//SCV가 이제 해당 위치까지 가야함
		vector<CObj*> vecUnit = CUnitControlMgr::Get_Instance()->GetVecUnitOrBuilding();
		if (vecUnit.size() >= 1)
		{
			POINT	Pt;
			GetCursorPos(&Pt);
			ScreenToClient(g_hWnd, &Pt);

			Pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
			Pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

			if (dynamic_cast<CObj_Dynamic*>(vecUnit.back()))
			{
				vector<wchar_t*> m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound(DYNAMIC_OBJ_SCV, SOUND_BUILD);
				CSoundMgr::Get_Instance()->PlaySound(m_UnitSound.back(), SOUND_SCV_BUILD, 1);

				CObj_Dynamic* target = dynamic_cast<CObj_Dynamic*>(vecUnit.back());
				target->ChangeStateWithMouse(Pt, BUILD_STATE);
				CUIMgr::Get_Instance()->SetClear_StaticObj();
				CKeyMgr::Get_Instance()->Set_bSelectUnit(false);
				CUnitControlMgr::Get_Instance()->Set_Clear_Unit();
			}
		}
	}
	else
	{
		CUIMgr::Get_Instance()->SetClear_Dynamic_Obj();
		CUnitControlMgr::Get_Instance()->Set_Clear_Unit();
		CKeyMgr::Get_Instance()->Set_bSelectUnit(false);
	}
}

void CLClick_Mouse::Release()
{
}

void CLClick_Mouse::Initialize()
{
	POINT	Pt;
	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	// UI창에 입력이 되었다면
	if (Pt.y > 450.f)
	{
		HandleUIClick(Pt);
	}
	else
	{
		Pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		Pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		//좌표에 해당하는 유닛을 반환한다.
		CObj* target = CObjMgr::Get_Instance()->Get_Target(Pt.x, Pt.y);

		if (target != nullptr)
		{
			if (dynamic_cast<CObj_Dynamic*>(target))
				HandleDynamicObjectClick(target);
			else if (dynamic_cast<CObj_Static*>(target))
				HandleStaticObjectClick(target);
		}
		else
		{
			HandleNoTargetClick();
		}
	}
}
