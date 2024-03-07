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
#include "Tank.h"
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
	{
		CUnitControlMgr::Get_Instance()->Set_Clear_Unit();
		CUIMgr::Get_Instance()->GetUIWireMgr()->SetClear_SmallWireObj();
	}

	CUIMgr::Get_Instance()->OnClickObj(target);
	CUnitControlMgr::Get_Instance()->Set_Add_Unit(target);
	CKeyMgr::Get_Instance()->Set_bSelectUnit(true);
	CTank* tank = dynamic_cast<CTank*>(target);
	CObj_Dynamic* dynamicTarget = dynamic_cast<CObj_Dynamic*>(target);

	vector<wchar_t*> m_UnitSound;

	switch (dynamicTarget->GetType())
	{
	case DYNAMIC_OBJ_SCV:
		m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound(DYNAMIC_OBJ_SCV, SOUND_BASIC);
		if (!m_UnitSound.empty()) {
			int random = rand() % m_UnitSound.size();
			CSoundMgr::Get_Instance()->PlaySound(m_UnitSound[random], SOUND_SCV_WALK, 1);
		}
		break;
	case DYNAMIC_OBJ_MARINE:
		m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound(DYNAMIC_OBJ_MARINE, SOUND_BASIC);
		if (!m_UnitSound.empty()) {
			int random = rand() % m_UnitSound.size();
			CSoundMgr::Get_Instance()->PlaySound(m_UnitSound[random], SOUND_MARINE_WALK, 1);
		}
		break;
	case DYNAMIC_OBJ_FIREBAT:
		m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound(DYNAMIC_OBJ_FIREBAT, SOUND_BASIC);
		if (!m_UnitSound.empty()) {
			int random = rand() % m_UnitSound.size();
			CSoundMgr::Get_Instance()->PlaySound(m_UnitSound[random], SOUND_FIREBAT_WALK, 1);
		}
		break;
	case DYNAMIC_OBJ_MEDIC:
		m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound(DYNAMIC_OBJ_MEDIC, SOUND_BASIC);
		if (!m_UnitSound.empty()) {
			int random = rand() % m_UnitSound.size();
			CSoundMgr::Get_Instance()->PlaySound(m_UnitSound[random], SOUND_MEDIC_WALK, 1);
		}
		break;
	case DYNAMIC_OBJ_TANK:
		m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound(DYNAMIC_OBJ_TANK, SOUND_BASIC);
		if (!m_UnitSound.empty()) {
			int random = rand() % m_UnitSound.size();
			CSoundMgr::Get_Instance()->PlaySound(m_UnitSound[random], SOUND_TANK_WALK, 1);
		}
		break;
	case DYNAMIC_OBJ_GHOST:
		m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound(DYNAMIC_OBJ_GHOST, SOUND_BASIC);
		if (!m_UnitSound.empty()) {
			int random = rand() % m_UnitSound.size();
			CSoundMgr::Get_Instance()->PlaySound(m_UnitSound[random], SOUND_GHOST_WALK, 1);
		}
		break;
	}

	if (tank)
	{
		if (tank->GetStateID() == SIEGEMODE_STATE)
			return;
	}
	else
	{
		if (dynamicTarget->GetStateID() != BUILD_STATE)
			dynamicTarget->ChangeState(IDLE_STATE);
	}
}

void CLClick_Mouse::HandleStaticObjectClick(CObj* target)
{
	if (CKeyMgr::Get_Instance()->Get_bSelectUnit())
	{
		CUnitControlMgr::Get_Instance()->Set_Clear_Unit();
		CUnitControlMgr::Get_Instance()->Set_Clear_Building();
		CUIMgr::Get_Instance()->SetClear_Dynamic_Obj();
	}

	CObj_Static* staticObj= dynamic_cast<CObj_Static*>(target);

	vector<wchar_t*> m_UnitSound;
	switch (staticObj->GetType())
	{
	case STATIC_OBJ_DEPOT:
		m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound((DYNAMIC_OBJID)SOUND_STATIC_OBJ_DEPOT, SOUND_BUILDING);
		CSoundMgr::Get_Instance()->PlaySound(m_UnitSound.back(), SOUND_DEPOT, 1);
		break;
	case STATIC_OBJ_ACADENY:
		m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound((DYNAMIC_OBJID)SOUND_STATIC_OBJ_ACADENY, SOUND_BUILDING);
		CSoundMgr::Get_Instance()->PlaySound(m_UnitSound.back(), SOUND_ACADEMY, 1);
		break;
	case STATIC_OBJ_FACTORY_ADDON:
		m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound((DYNAMIC_OBJID)SOUND_STATIC_OBJ_FACTORY_ADDON, SOUND_BUILDING);
		CSoundMgr::Get_Instance()->PlaySound(m_UnitSound.back(), SOUND_FACTORY_ADDON, 1);
		break;
	case STATIC_OBJ_SCIENCE_FACILITY:
		m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound((DYNAMIC_OBJID)SOUND_STATIC_OBJ_SCIENCE_FACILITY, SOUND_BUILDING);
		CSoundMgr::Get_Instance()->PlaySound(m_UnitSound.back(), SOUND_SCIENCE, 1);
		break;
	case STATIC_OBJ_SCIENCE_FACILITY_ADDON:
		m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound((DYNAMIC_OBJID)SOUND_STATIC_OBJ_SCIENCE_FACILITY_ADDON, SOUND_BUILDING);
		CSoundMgr::Get_Instance()->PlaySound(m_UnitSound.back(), SOUND_SCIENCE_ADDON, 1);
		break;
	}
	

	CUnitControlMgr::Get_Instance()->Set_Add_Building(target);
	CKeyMgr::Get_Instance()->Set_bSelectUnit(true);
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
		bool hasNuclear = CUIMgr::Get_Instance()->GetNuclear();

		//왼쪽 클릭을 했는데 타겟이 있다면
		if (target != nullptr)
		{
			if (hasNuclear)
			{

			}
			else if (dynamic_cast<CObj_Dynamic*>(target))
				HandleDynamicObjectClick(target);
			else if (dynamic_cast<CObj_Static*>(target))
				HandleStaticObjectClick(target);
		}
		else
		{
			if (hasNuclear)
			{

			}
			else
				HandleNoTargetClick();
		}

		if (hasNuclear)
		{
			//고스트는 한마리만 뽑자.
			CObj* ghost = CObjMgr::Get_Instance()->GetDynamic_Obj_List()[DYNAMIC_OBJ_GHOST].back();
			CObj_Dynamic* dynamicGhost = dynamic_cast<CObj_Dynamic*>(ghost);
			if (dynamicGhost == nullptr)
				return;

			POINT	Pt;
			GetCursorPos(&Pt);
			ScreenToClient(g_hWnd, &Pt);

			Pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
			Pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

			dynamicGhost->ChangeStateWithMouse(Pt, ATTACK_STATE);
			CUIMgr::Get_Instance()->SetNuclear(false);
		}
	}
}
