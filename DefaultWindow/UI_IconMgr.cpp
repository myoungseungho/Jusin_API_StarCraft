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

CUI_IconMgr::CUI_IconMgr() : m_MoveIcon(nullptr), m_StopIcon(nullptr), m_AttackIcon(nullptr), m_BuildIcon(nullptr)
, m_AdvancedbuildIcon(nullptr), m_CenterIcon(nullptr), m_BarrackIcon(nullptr), m_DepotIcon(nullptr), m_FactoryIcon(nullptr), m_StarPortIcon(nullptr),
m_center(nullptr), m_depot(nullptr), m_barrack(nullptr), m_factory(nullptr), m_starport(nullptr), m_CurrentBuilding(UI_STATIC_OBJ_END),
m_ScvIcon(nullptr), m_MarineIcon(nullptr), m_FireBatIcon(nullptr), m_MedicIcon(nullptr), m_TankIcon(nullptr)
{
}

CUI_IconMgr::~CUI_IconMgr()
{
}

void CUI_IconMgr::Initialize()
{
	m_vecBuildingIcon.push_back(m_ScvIcon);
	m_vecBuildingIcon.push_back(m_MarineIcon);
	m_vecBuildingIcon.push_back(m_FireBatIcon);
	m_vecBuildingIcon.push_back(m_MedicIcon);
	m_vecBuildingIcon.push_back(m_TankIcon);
}

void CUI_IconMgr::OnClickObj(CObj* _unit)
{
	SetClear_IconObj();

	CObj_Dynamic* dynamic_unit = dynamic_cast<CObj_Dynamic*>(_unit);
	CObj_Static* staticObj = dynamic_cast<CObj_Static*>(_unit);

	if (dynamic_unit != nullptr)
	{
		DynamicSetUI(dynamic_unit->GetType());
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
	}
	else if (ICONId == ICON_ADVANCED_BUILD)
	{
		m_vecUnitIcon.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Factory_Icon>(UI_OBJECT_ICON, 655.f, 468.f));
		m_vecUnitIcon.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_StarPort_Icon>(UI_OBJECT_ICON, 655.f, 518.f));
		bool bCanBuildFactory = CTechTreeMgr::Get_Instance()->GetCanBuild(STATIC_OBJ_FACTORY);
		bool bCanBuildStarPort = CTechTreeMgr::Get_Instance()->GetCanBuild(STATIC_OBJ_STARPORT);

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
			}
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
	else if (ICONId == ICON_SCV)
	{
		CObj* obj = CUnitControlMgr::Get_Instance()->GetBuilding();
		dynamic_cast<CObj_Static*>(obj)->Spawn_Unit(DYNAMIC_OBJ_SCV);
	}
	else if (ICONId == ICON_MARINE)
	{
		CObj* obj = CUnitControlMgr::Get_Instance()->GetBuilding();
		dynamic_cast<CObj_Static*>(obj)->Spawn_Unit(DYNAMIC_OBJ_MARINE);
	}
	else if (ICONId == ICON_FIREBAT)
	{
		CObj* obj = CUnitControlMgr::Get_Instance()->GetBuilding();
		dynamic_cast<CObj_Static*>(obj)->Spawn_Unit(DYNAMIC_OBJ_FIREBAT);
	}
	else if (ICONId == ICON_MEDIC)
	{
		CObj* obj = CUnitControlMgr::Get_Instance()->GetBuilding();
		dynamic_cast<CObj_Static*>(obj)->Spawn_Unit(DYNAMIC_OBJ_MEDIC);
	}
	else if (ICONId == ICON_TANK)
	{
		CObj* obj = CUnitControlMgr::Get_Instance()->GetBuilding();
		dynamic_cast<CObj_Static*>(obj)->Spawn_Unit(DYNAMIC_OBJ_TANK);
	}
}

void CUI_IconMgr::SetClear_IconObj()
{
	for (auto iter : m_vecUnitIcon)
	{
		if (iter != nullptr)
			iter->Set_Dead();
	}

	for (auto iter : m_vecBuildingIcon)
	{
		if (iter != nullptr)
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
		if (iter != nullptr)
			iter->Set_Dead();
	}

	m_vecBuilding.clear();
	m_vecBuilding.shrink_to_fit();
}

void CUI_IconMgr::DynamicSetUI(DYNAMIC_OBJID objId)
{
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
	else if (objId == DYNAMIC_OBJ_MARINE || objId == DYNAMIC_OBJ_FIREBAT || objId == DYNAMIC_OBJ_MEDIC || objId == DYNAMIC_OBJ_TANK)
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

		for (auto iter : m_vecBuildingIcon)
		{
			if (iter == nullptr || iter->Get_Dead())
				continue;

			if (iter->GetDetailType() == ICON_FIREBAT || iter->GetDetailType() == ICON_MEDIC)
			{
				iter->Get_Frame()->iFrameStart = 1;
			}
		}
	}
	else if (objId == STATIC_OBJ_FACTORY)
	{
		m_vecBuildingIcon.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Tank_Icon>(UI_OBJECT_ICON, 655.f, 468.f));
		for (auto iter : m_vecBuildingIcon)
		{
			if (iter == nullptr || iter->Get_Dead())
				continue;

			if (iter->GetDetailType() == ICON_TANK)
			{
				iter->Get_Frame()->iFrameStart = 1;
				return;
			}
		}
	}
}
