#include "stdafx.h"
#include "UI_IconMgr.h"
#include "BmpMgr.h"
#include "Obj_Dynamic.h"
#include "UnitControlMgr.h"
#include "SpawnMgr.h"
#include "UI_Move.h"
#include "UI_Stop_Icon.h"
#include "UI_Attack.h"
#include "UI_Build.h"
#include "UI_Advanced_Build.h"
#include "UI_Center.h"
#include "UI_Barrack.h"
#include "UI_Depot.h"
#include "UI_Factory.h"
#include "UI_StarPort.h"
#include "UI_Attack.h"
#include "UI_Factory_Addon_Icon.h"
#include "UI_Academy_Icon.h"
#include "UI_Science_Facility_Icon.h"
#include "UI_Science_Facility_Addon_Icon.h"
#include "ScrollMgr.h"
#include "Center.h"
#include "SupplyDepot.h"
#include "Barrack.h"
#include "Factory.h"
#include "Starport.h"
#include "Center_UI.h"
#include "Depot_UI.h"
#include "Barrack_UI.h"
#include "Factory_UI.h"
#include "StarPort_UI.h"
#include "Academy_UI.h"
#include "TechTreeMgr.h"
#include "UI_SCV_Icon.h"
#include "UI_Marine_Icon.h"
#include "UI_FireBat_Icon.h"
#include "UI_Medic_Icon.h"
#include "UI_Tank_Icon.h"
#include "Scv.h"
#include "Marine.h"
#include "FireBat.h"
#include "Medic.h"
#include "Tank.h"
#include "SoundMgr.h"
#include "EconomyMgr.h"
#include "UI_SiegeMode_Icon.h"
#include "UI_DefaultMode.h"
#include "Tank_Siege_Mode.h"
#include "Ghost.h"
#include "UI_Nuclear_Icon.h"
#include "UI_Factory_Addon_Icon.h"
#include "Science_Facility_UI.h"
#include "Factory_Addon.h"
#include "Science_Facility_Addon.h"
#include "UI_Ghost_Icon.h"
CUI_IconMgr::CUI_IconMgr() :m_CurrentBuilding(UI_STATIC_OBJ_END), m_GhostNuclear(false)
{
}

CUI_IconMgr::~CUI_IconMgr()
{
}

void CUI_IconMgr::Initialize()
{

}


void CUI_IconMgr::OnClickObj(CObj* _unit)
{
	SetClear_IconObj();

	CObj_Dynamic* dynamic_unit = dynamic_cast<CObj_Dynamic*>(_unit);
	CObj_Static* staticObj = dynamic_cast<CObj_Static*>(_unit);

	if (dynamic_unit != nullptr)
	{
		DynamicSetUI(_unit);
		return;
	}

	if (staticObj != nullptr)
	{
		StaticSetUI(staticObj->GetType());
		return;
	}
}

void CUI_IconMgr::OnClickIcon(CObj* _unit)
{
	int ICONId = dynamic_cast<CObj_UI*>(_unit)->GetDetailType();

	//건물이라면
	if (dynamic_cast<CObj_Static*>(CUnitControlMgr::Get_Instance()->GetVecUnitOrBuilding().back()))
	{

	}
	else
		SetClear_IconObj();

	if (ICONId == ICON_BUILD)
	{
		m_vecUnitIcon.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Center_Icon>(UI_OBJECT_ICON, 655.f, 468.f));
		m_vecUnitIcon.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Depot_Icon>(UI_OBJECT_ICON, 713.f, 468.f));
		m_vecUnitIcon.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Barrack_Icon>(UI_OBJECT_ICON, 655.f, 518.f));
		m_vecUnitIcon.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Academy_Icon>(UI_OBJECT_ICON, 655.f, 570.f));
		bool bCanBuildAcademy = CTechTreeMgr::Get_Instance()->GetCanBuild(STATIC_OBJ_ACADENY);
		if (bCanBuildAcademy)
		{
			for (auto iter : m_vecUnitIcon)
			{
				if (iter->GetDetailType() == ICON_ACADEMY)
					iter->Get_Frame()->iFrameStart = 1;
			}
		}
	}
	else if (ICONId == ICON_ADVANCED_BUILD)
	{
		m_vecUnitIcon.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Factory_Icon>(UI_OBJECT_ICON, 655.f, 468.f));
		m_vecUnitIcon.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_StarPort_Icon>(UI_OBJECT_ICON, 713.f, 468.f));
		m_vecUnitIcon.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Science_Facility_Icon>(UI_OBJECT_ICON, 768.f, 468.f));
		bool bCanBuildFactory = CTechTreeMgr::Get_Instance()->GetCanBuild(STATIC_OBJ_FACTORY);
		bool bCanBuildStarPort = CTechTreeMgr::Get_Instance()->GetCanBuild(STATIC_OBJ_STARPORT);
		bool bCanBuildScienceFacility = CTechTreeMgr::Get_Instance()->GetCanBuild(STATIC_OBJ_SCIENCE_FACILITY);
		if (bCanBuildFactory)
		{
			for (auto iter : m_vecUnitIcon)
			{
				if (iter->GetDetailType() == ICON_FACTORY)
					iter->Get_Frame()->iFrameStart = 1;
			}

			if (bCanBuildStarPort)
			{
				for (auto iter : m_vecUnitIcon)
				{
					if (iter->GetDetailType() == ICON_STARPORT)
						iter->Get_Frame()->iFrameStart = 1;
				}

				if (bCanBuildScienceFacility)
				{
					for (auto iter : m_vecUnitIcon)
					{
						if (iter->GetDetailType() == ICON_SCIENCE_FACILITY)
							iter->Get_Frame()->iFrameStart = 1;
					}
				}
			}
		}
	}
	else if (ICONId == ICON_SIEGE_MODE)
	{
		vector<CObj*> vecUnit = CUnitControlMgr::Get_Instance()->GetVecUnitOrBuilding();
		for (auto iter : vecUnit)
		{
			CObj_Dynamic* dynamicObj = dynamic_cast<CObj_Dynamic*>(iter);
			if (dynamicObj != nullptr)
				if (dynamicObj->GetType() == DYNAMIC_OBJ_TANK)
				{
					dynamicObj->ChangeState(SIEGEMODE_STATE);
				}
		}

	}
	else if (ICONId == ICON_DEFAULT_MODE)
	{
		vector<CObj*> vecUnit = CUnitControlMgr::Get_Instance()->GetVecUnitOrBuilding();
		for (auto iter : vecUnit)
		{
			CTank* tankObj = dynamic_cast<CTank*>(iter);

			dynamic_cast<CTank_Siege_Mode*>(tankObj->GetCurrentState(SIEGEMODE_STATE))->SetDefaultMode();
		}
	}
	else if (ICONId == ICON_CENTER)
	{
		m_vecBuilding.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CCenter_UI>(UI_OBJECT_BUILD, 0.f, 0.f));
		m_CurrentBuilding = UI_STATIC_OBJ_CENTER;
	}
	else if (ICONId == ICON_DEPOT)
	{
		m_vecBuilding.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CDepot_UI>(UI_OBJECT_BUILD, 0.f, 0.f));
		m_CurrentBuilding = UI_STATIC_OBJ_DEPOT;
	}
	else if (ICONId == ICON_BARRACK)
	{
		m_vecBuilding.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CBarrack_UI>(UI_OBJECT_BUILD, 0.f, 0.f));
		m_CurrentBuilding = UI_STATIC_OBJ_BARRACK;
	}
	else if (ICONId == ICON_ACADEMY)
	{
		bool bCanBuildAcademy = CTechTreeMgr::Get_Instance()->GetCanBuild(STATIC_OBJ_ACADENY);

		if (!bCanBuildAcademy)
			return;

		m_vecBuilding.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CAcademy_UI>(UI_OBJECT_BUILD, 0.f, 0.f));
		m_CurrentBuilding = UI_STATIC_OBJ_ACADEMY;
	}
	else if (ICONId == ICON_FACTORY)
	{
		bool bCanBuildFactory = CTechTreeMgr::Get_Instance()->GetCanBuild(STATIC_OBJ_FACTORY);

		if (!bCanBuildFactory)
			return;

		m_vecBuilding.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CFactory_UI>(UI_OBJECT_BUILD, 0.f, 0.f));
		m_CurrentBuilding = UI_STATIC_OBJ_FACTORY;
	}
	else if (ICONId == ICON_STARPORT)
	{
		bool bCanBuildStarPort = CTechTreeMgr::Get_Instance()->GetCanBuild(STATIC_OBJ_STARPORT);

		if (!bCanBuildStarPort)
			return;

		m_vecBuilding.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CStarPort_UI>(UI_OBJECT_BUILD, 0.f, 0.f));
		m_CurrentBuilding = UI_STATIC_OBJ_STARPORT;
	}
	else if (ICONId == ICON_SCIENCE_FACILITY)
	{
		bool bCanBuildScienceFacility = CTechTreeMgr::Get_Instance()->GetCanBuild(STATIC_OBJ_SCIENCE_FACILITY);

		if (!bCanBuildScienceFacility)
			return;

		m_vecBuilding.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CScience_Facility_UI>(UI_OBJECT_BUILD, 0.f, 0.f));
		m_CurrentBuilding = UI_STATIC_OBJ_SCIENCE_FACILITY;
	}
	else if (ICONId == ICON_FACTORY_ADDON)
	{
		CObj* factory = CObjMgr::Get_Instance()->GetStatic_Obj_List()[STATIC_OBJ_FACTORY].back();
		if (factory != nullptr)
		{
			float top = factory->Get_Rect().bottom - 60.f;
			float right = factory->Get_Rect().right + 30.f;
			CTechTreeMgr::Get_Instance()->SetBuiding(STATIC_OBJ_FACTORY_ADDON);
			CTechTreeMgr::Get_Instance()->SetIsFactory_Addon();
			CEconomyMgr::Get_Instance()->SetMineral(-50);
			CEconomyMgr::Get_Instance()->SetGas(-50);
			CSpawnMgr::Get_Instance()->Spawn_StaticObj<CFactory_Addon>(STATIC_OBJ_FACTORY_ADDON, FACTION_ALLY, right, top);
			_unit->Set_Dead();
		}
	}
	else if (ICONId == ICON_SCIENCE_FACILITY_ADDON)
	{
		CObj* science = CObjMgr::Get_Instance()->GetStatic_Obj_List()[STATIC_OBJ_SCIENCE_FACILITY].back();
		if (science != nullptr)
		{
			float top = science->Get_Rect().bottom - 60.f;
			float right = science->Get_Rect().right + 30.f;
			CTechTreeMgr::Get_Instance()->SetBuiding(STATIC_OBJ_SCIENCE_FACILITY_ADDON);
			CTechTreeMgr::Get_Instance()->SetIsScience_Addon();
			CEconomyMgr::Get_Instance()->SetMineral(-50);
			CEconomyMgr::Get_Instance()->SetGas(-50);
			CSpawnMgr::Get_Instance()->Spawn_StaticObj<CScience_Facility_Addon>(STATIC_OBJ_SCIENCE_FACILITY_ADDON, FACTION_ALLY, right, top);
			_unit->Set_Dead();
		}
	}
	else if (ICONId == ICON_SCV)
	{
		CObj* obj = CUnitControlMgr::Get_Instance()->GetBuilding();
		dynamic_cast<CObj_Static*>(obj)->Spawn_Unit(DYNAMIC_OBJ_SCV);

		vector<wchar_t*> m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound(DYNAMIC_OBJ_SCV, SOUND_READY);
		CSoundMgr::Get_Instance()->PlaySound(m_UnitSound.back(), SOUND_SCV_READY, 1);
		CEconomyMgr::Get_Instance()->SetMineral(-50);
		CEconomyMgr::Get_Instance()->SetPeople(1);
	}
	else if (ICONId == ICON_MARINE)
	{
		CObj* obj = CUnitControlMgr::Get_Instance()->GetBuilding();
		dynamic_cast<CObj_Static*>(obj)->Spawn_Unit(DYNAMIC_OBJ_MARINE);

		vector<wchar_t*> m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound(DYNAMIC_OBJ_MARINE, SOUND_READY);
		CSoundMgr::Get_Instance()->PlaySound(m_UnitSound.back(), SOUND_MARINE_READY, 1);
		CEconomyMgr::Get_Instance()->SetMineral(-50);
		CEconomyMgr::Get_Instance()->SetPeople(1);
	}
	else if (ICONId == ICON_FIREBAT)
	{
		if (CTechTreeMgr::Get_Instance()->GetIsAcademy())
		{
			CObj* obj = CUnitControlMgr::Get_Instance()->GetBuilding();
			dynamic_cast<CObj_Static*>(obj)->Spawn_Unit(DYNAMIC_OBJ_FIREBAT);

			vector<wchar_t*> m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound(DYNAMIC_OBJ_FIREBAT, SOUND_READY);
			CSoundMgr::Get_Instance()->PlaySound(m_UnitSound.back(), SOUND_FIREBAT_READY, 1);
			CEconomyMgr::Get_Instance()->SetMineral(-50);
			CEconomyMgr::Get_Instance()->SetGas(-25);
			CEconomyMgr::Get_Instance()->SetPeople(1);
		}
	}
	else if (ICONId == ICON_MEDIC)
	{
		if (CTechTreeMgr::Get_Instance()->GetIsAcademy())
		{
			CObj* obj = CUnitControlMgr::Get_Instance()->GetBuilding();
			dynamic_cast<CObj_Static*>(obj)->Spawn_Unit(DYNAMIC_OBJ_MEDIC);

			vector<wchar_t*> m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound(DYNAMIC_OBJ_MEDIC, SOUND_READY);
			CSoundMgr::Get_Instance()->PlaySound(m_UnitSound.back(), SOUND_MEDIC_READY, 1);
			CEconomyMgr::Get_Instance()->SetMineral(-50);
			CEconomyMgr::Get_Instance()->SetGas(-25);
			CEconomyMgr::Get_Instance()->SetPeople(1);
		}
	}
	else if (ICONId == ICON_TANK)
	{
		if (CTechTreeMgr::Get_Instance()->GetIsFactory_Addon())
		{
			CObj* obj = CUnitControlMgr::Get_Instance()->GetBuilding();
			dynamic_cast<CObj_Static*>(obj)->Spawn_Unit(DYNAMIC_OBJ_TANK);

			vector<wchar_t*> m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound(DYNAMIC_OBJ_TANK, SOUND_READY);
			CSoundMgr::Get_Instance()->PlaySound(m_UnitSound.back(), SOUND_TANK_READY, 1);
			CEconomyMgr::Get_Instance()->SetMineral(-150);
			CEconomyMgr::Get_Instance()->SetGas(-100);
			CEconomyMgr::Get_Instance()->SetPeople(2);
		}
	}
	else if (ICONId == ICON_NUCLEAR)
	{
		m_GhostNuclear = true;
	}
}

void CUI_IconMgr::OnDragObj()
{
	bool bOnlyTank = true;
	bool bOnlySTank = true;

	vector<CObj*> vecUnit = CUnitControlMgr::Get_Instance()->GetVecUnitOrBuilding();

	for (auto iter : vecUnit)
	{
		CObj_Dynamic* dynamicObj = dynamic_cast<CObj_Dynamic*>(iter);

		if (dynamicObj->GetType() != DYNAMIC_OBJ_TANK)
		{
			bOnlyTank = false;
			bOnlySTank = false;
			break;
		}
		else
		{
			if (dynamicObj->GetStateID() != SIEGEMODE_STATE)
			{
				bOnlySTank = false;
				break;
			}
			else
			{
				bOnlyTank = false;
			}
		}
	}

	if (bOnlyTank)
	{
		for (auto iter : vecUnit)
		{
			m_vecUnitIcon.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_SiegeMode_Icon>(UI_OBJECT_ICON, 655.f, 570.f));
		}
	}
	else if (bOnlySTank)
	{
		for (auto iter : vecUnit)
		{
			m_vecUnitIcon.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_DefaultMode>(UI_OBJECT_ICON, 655.f, 570.f));
		}
	}
}

void CUI_IconMgr::SetClear_IconObj()
{
	for (auto iter : m_vecUnitIcon)
	{
		if (iter == nullptr || iter->Get_Dead())
			continue;

		iter->Set_Dead();
	}

	for (auto iter : m_vecBuildingIcon)
	{
		if (iter == nullptr || iter->Get_Dead())
			continue;

		iter->Set_Dead();
	}

	m_vecUnitIcon.clear();
	m_vecUnitIcon.shrink_to_fit();
	m_vecBuildingIcon.clear();
	m_vecBuildingIcon.shrink_to_fit();
}

void CUI_IconMgr::SetClear_StaticObj()
{
	for (auto iter : m_vecBuilding)
	{
		if (iter != nullptr || !iter->Get_Dead())
			iter->Set_Dead();
	}

	m_vecBuilding.clear();
	m_vecBuilding.shrink_to_fit();
}

void CUI_IconMgr::DynamicSetUI(CObj* _unit)
{
	DYNAMIC_OBJID objId = dynamic_cast<CObj_Dynamic*>(_unit)->GetType();

	if (objId == DYNAMIC_OBJ_SCV)
	{
		m_vecUnitIcon.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Move_Icon>(UI_OBJECT_ICON, 655.f, 468.f));
		m_vecUnitIcon.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Stop_Icon>(UI_OBJECT_ICON, 713.f, 468.f));
		m_vecUnitIcon.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Attack_Icon>(UI_OBJECT_ICON, 768.f, 468.f));
		m_vecUnitIcon.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Build_Icon>(UI_OBJECT_ICON, 655.f, 570.f));
		m_vecUnitIcon.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Advanced_Build_Icon>(UI_OBJECT_ICON, 715.f, 570.f));

		for (auto iter : m_vecUnitIcon)
		{
			if (iter == nullptr || iter->Get_Dead())
				continue;

			if (iter->GetDetailType() == ICON_MOVE)
				iter->Get_Frame()->iFrameStart = 1;

			if (iter->GetDetailType() == ICON_STOP)
				iter->Get_Frame()->iFrameStart = 1;

			if (iter->GetDetailType() == ICON_ATTACK)
				iter->Get_Frame()->iFrameStart = 1;
		}
	}
	else if (objId == DYNAMIC_OBJ_MARINE || objId == DYNAMIC_OBJ_FIREBAT || objId == DYNAMIC_OBJ_MEDIC || objId == DYNAMIC_OBJ_TANK || objId == DYNAMIC_OBJ_GHOST)
	{
		m_vecUnitIcon.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Move_Icon>(UI_OBJECT_ICON, 655.f, 468.f));
		m_vecUnitIcon.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Stop_Icon>(UI_OBJECT_ICON, 713.f, 468.f));
		m_vecUnitIcon.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Attack_Icon>(UI_OBJECT_ICON, 768.f, 468.f));

		for (auto iter : m_vecUnitIcon)
		{
			if (iter == nullptr || iter->Get_Dead())
				continue;

			if (iter->GetDetailType() == ICON_MOVE)
				iter->Get_Frame()->iFrameStart = 1;

			if (iter->GetDetailType() == ICON_STOP)
				iter->Get_Frame()->iFrameStart = 1;

			if (iter->GetDetailType() == ICON_ATTACK)
				iter->Get_Frame()->iFrameStart = 1;
		}

		if (objId == DYNAMIC_OBJ_TANK)
		{
			CTank* dynamicObj = dynamic_cast<CTank*>(_unit);
			if (dynamicObj != nullptr)
				if (dynamicObj->GetStateID() == SIEGEMODE_STATE)
				{
					m_vecUnitIcon.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_DefaultMode>(UI_OBJECT_ICON, 655.f, 570.f));
				}
				else
				{
					m_vecUnitIcon.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_SiegeMode_Icon>(UI_OBJECT_ICON, 655.f, 570.f));
				}
		}

		if (objId == DYNAMIC_OBJ_GHOST)
		{
			CGhost* dynamicObj = dynamic_cast<CGhost*>(_unit);
			if (dynamicObj != nullptr)
				m_vecUnitIcon.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Nuclear_Icon>(UI_OBJECT_ICON, 655.f, 570.f));
		}
	}
}

void CUI_IconMgr::StaticSetUI(BUILDINGSTATE objId)
{
	if (objId == STATIC_OBJ_CENTER)
	{
		m_vecBuildingIcon.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_SCV_Icon>(UI_OBJECT_ICON, 655.f, 468.f));
	}
	else if (objId == STATIC_OBJ_BARRACK)
	{
		m_vecBuildingIcon.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Marine_Icon>(UI_OBJECT_ICON, 655.f, 468.f));
		m_vecBuildingIcon.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_FireBat_Icon>(UI_OBJECT_ICON, 713.f, 468.f));
		m_vecBuildingIcon.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Medic_Icon>(UI_OBJECT_ICON, 768.f, 468.f));
		m_vecBuildingIcon.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Ghost_Icon>(UI_OBJECT_ICON, 655.f, 518.f));

		for (auto iter : m_vecBuildingIcon)
		{
			if (iter == nullptr || iter->Get_Dead())
				continue;

			if (CTechTreeMgr::Get_Instance()->GetIsAcademy())
			{
				if (iter->GetDetailType() == ICON_FIREBAT || iter->GetDetailType() == ICON_MEDIC)
				{
					iter->Get_Frame()->iFrameStart = 1;
				}
			}

			if (CTechTreeMgr::Get_Instance()->GetIsScience_Addon())
			{
				if (iter->GetDetailType() == ICON_GHOST)
				{
					iter->Get_Frame()->iFrameStart = 1;
				}
			}
		}
	}
	else if (objId == STATIC_OBJ_FACTORY)
	{
		m_vecBuildingIcon.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Tank_Icon>(UI_OBJECT_ICON, 655.f, 468.f));
		m_vecBuildingIcon.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Factory_Addon_Icon>(UI_OBJECT_ICON, 655.f, 570.f));

		for (auto iter : m_vecBuildingIcon)
		{
			if (iter == nullptr || iter->Get_Dead())
				continue;

			if (CTechTreeMgr::Get_Instance()->GetIsFactory_Addon())
			{
				if (iter->GetDetailType() == ICON_TANK)
				{
					iter->Get_Frame()->iFrameStart = 1;
				}

				if (iter->GetDetailType() == ICON_FACTORY_ADDON)
					iter->Set_Dead();
			}
			else
			{
				if (iter->GetDetailType() == ICON_FACTORY_ADDON)
				{
					iter->Get_Frame()->iFrameStart = 1;
				}
			}


		}
	}
	else if (objId == STATIC_OBJ_SCIENCE_FACILITY)
	{
		m_vecBuildingIcon.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Science_Facility_Addon_Icon>(UI_OBJECT_ICON, 655.f, 570.f));

		for (auto iter : m_vecBuildingIcon)
		{
			if (iter == nullptr || iter->Get_Dead())
				continue;

			if (CTechTreeMgr::Get_Instance()->GetIsScience_Addon())
			{
				if (iter->GetDetailType() == ICON_SCIENCE_FACILITY_ADDON)
				{
					iter->Set_Dead();
				}
			}
			else
			{
				if (iter->GetDetailType() == ICON_SCIENCE_FACILITY_ADDON)
				{
					iter->Get_Frame()->iFrameStart = 1;
				}
			}

		}
	}
}
