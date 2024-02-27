#include "stdafx.h"
#include "UIMgr.h"
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
CUIMgr* CUIMgr::m_pInstance = nullptr;

CUIMgr::CUIMgr() :m_MoveIcon(nullptr), m_StopIcon(nullptr), m_AttackIcon(nullptr), m_BuildIcon(nullptr)
, m_AdvancedbuildIcon(nullptr), m_CenterIcon(nullptr), m_BarrackIcon(nullptr), m_DepotIcon(nullptr), m_FactoryIcon(nullptr), m_StarPortIcon(nullptr),
m_center(nullptr), m_depot(nullptr), m_barrack(nullptr), m_factory(nullptr), m_starport(nullptr), m_CurrentBuilding(UI_STATIC_OBJ_END),
m_ScvIcon(nullptr), m_MarineIcon(nullptr), m_FireBatIcon(nullptr), m_MedicIcon(nullptr), m_TankIcon(nullptr)
{

}

CUIMgr::~CUIMgr()
{
}

void CUIMgr::Initialize()
{
	m_vecUnitIcon.push_back(m_MoveIcon);
	m_vecUnitIcon.push_back(m_StopIcon);
	m_vecUnitIcon.push_back(m_AttackIcon);
	m_vecUnitIcon.push_back(m_BuildIcon);
	m_vecUnitIcon.push_back(m_AdvancedbuildIcon);
	m_vecUnitIcon.push_back(m_CenterIcon);
	m_vecUnitIcon.push_back(m_BarrackIcon);
	m_vecUnitIcon.push_back(m_DepotIcon);
	m_vecUnitIcon.push_back(m_FactoryIcon);
	m_vecUnitIcon.push_back(m_StarPortIcon);

	m_vecBuilding.push_back(m_center);
	m_vecBuilding.push_back(m_depot);
	m_vecBuilding.push_back(m_barrack);
	m_vecBuilding.push_back(m_factory);
	m_vecBuilding.push_back(m_starport);

	m_vecBuildingIcon.push_back(m_ScvIcon);
	m_vecBuildingIcon.push_back(m_MarineIcon);
	m_vecBuildingIcon.push_back(m_FireBatIcon);
	m_vecBuildingIcon.push_back(m_MedicIcon);
	m_vecBuildingIcon.push_back(m_TankIcon);
}

void CUIMgr::Render(HDC hDC)
{

}

void CUIMgr::Release()
{

}

void CUIMgr::OnClickUnit(CObj* _unit)
{
	SetClear_IconObj();

	CObj_Dynamic* dynamic_unit = dynamic_cast<CObj_Dynamic*>(_unit);
	CObj_Static* staticObj = dynamic_cast<CObj_Static*>(_unit);

	if (dynamic_unit != nullptr)
		DynamicSetUI(dynamic_unit->GetType());

	if (staticObj != nullptr)
		StaticSetUI(staticObj->GetType());
}

void CUIMgr::OnClickIcon(CObj* _unit)
{
	ICONSTATE ICONId = dynamic_cast<CObj_UI*>(_unit)->GetType();

	if (CUnitControlMgr::Get_Instance()->GetBuilding())
	{

	}
	else
		SetClear_IconObj();


	if (ICONId == ICON_BUILD)
	{
		m_vecUnitIcon[ICON_CENTER] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Center_Icon>(UI_OBJ_ICON, 655.f, 468.f);
		m_vecUnitIcon[ICON_DEPOT] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Depot_Icon>(UI_OBJ_ICON, 713.f, 468.f);
		m_vecUnitIcon[ICON_BARRACK] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Barrack_Icon>(UI_OBJ_ICON, 655.f, 518.f);
	}
	else if (ICONId == ICON_ADVANCED_BUILD)
	{
		m_vecUnitIcon[ICON_FACTORY] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Factory_Icon>(UI_OBJ_ICON, 655.f, 468.f);
		m_vecUnitIcon[ICON_STARPORT] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_StarPort_Icon>(UI_OBJ_ICON, 655.f, 518.f);
		bool bCanBuildFactory = CTechTreeMgr::Get_Instance()->GetCanBuild(STATIC_OBJ_FACTORY);
		bool bCanBuildStarPort = CTechTreeMgr::Get_Instance()->GetCanBuild(STATIC_OBJ_STARPORT);

		if (bCanBuildFactory)
		{
			m_vecUnitIcon[ICON_FACTORY]->SetDrawID(1);

			if (bCanBuildStarPort)
				m_vecUnitIcon[ICON_STARPORT]->SetDrawID(1);
		}

	}
	else if (ICONId == ICON_CENTER)
	{
		m_vecBuilding[UI_STATIC_OBJ_CENTER] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CCenter_UI>(UI_OBJ_BUILDING, 0.f, 0.f);
		m_CurrentBuilding = UI_STATIC_OBJ_CENTER;
	}
	else if (ICONId == ICON_DEPOT)
	{
		m_vecBuilding[UI_STATIC_OBJ_DEPOT] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CDepot_UI>(UI_OBJ_BUILDING, 0.f, 0.f);
		m_CurrentBuilding = UI_STATIC_OBJ_DEPOT;
	}
	else if (ICONId == ICON_BARRACK)
	{
		m_vecBuilding[UI_STATIC_OBJ_BARRACK] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CBarrack_UI>(UI_OBJ_BUILDING, 0.f, 0.f);
		m_CurrentBuilding = UI_STATIC_OBJ_BARRACK;
	}
	else if (ICONId == ICON_FACTORY)
	{
		bool bCanBuildFactory = CTechTreeMgr::Get_Instance()->GetCanBuild(STATIC_OBJ_FACTORY);

		if (!bCanBuildFactory)
			return;

		m_vecBuilding[UI_STATIC_OBJ_FACTORY] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CFactory_UI>(UI_OBJ_BUILDING, 0.f, 0.f);
		m_CurrentBuilding = UI_STATIC_OBJ_FACTORY;

	}
	else if (ICONId == ICON_STARPORT)
	{
		bool bCanBuildStarPort = CTechTreeMgr::Get_Instance()->GetCanBuild(STATIC_OBJ_STARPORT);

		if (!bCanBuildStarPort)
			return;

		m_vecBuilding[UI_STATIC_OBJ_STARPORT] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CStarPort_UI>(UI_OBJ_BUILDING, 0.f, 0.f);
		m_CurrentBuilding = UI_STATIC_OBJ_STARPORT;
	}
	else if (ICONId == ICON_SCV)
	{
		CObj* obj = CUnitControlMgr::Get_Instance()->GetBuilding();
		dynamic_cast<CObj_Static*>(obj)->Spawn_Unit(DYANMIC_OBJ_SCV);
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

void CUIMgr::SetClear_IconObj()
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
}

void CUIMgr::SetClear_StaticObj()
{
	for (auto iter : m_vecBuilding)
	{
		if (iter != nullptr)
			iter->Set_Dead();
	}
}

void CUIMgr::DynamicSetUI(DYNAMIC_OBJID objId)
{
	if (objId == DYANMIC_OBJ_SCV)
	{
		m_vecUnitIcon[ICON_MOVE] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Move_Icon>(UI_OBJ_ICON, 655.f, 468.f);
		m_vecUnitIcon[ICON_STOP] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Stop_Icon>(UI_OBJ_ICON, 713.f, 468.f);
		m_vecUnitIcon[ICON_ATTACK] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Attack_Icon>(UI_OBJ_ICON, 768.f, 468.f);
		m_vecUnitIcon[ICON_BUILD] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Build_Icon>(UI_OBJ_ICON, 655.f, 570.f);
		m_vecUnitIcon[ICON_ADVANCED_BUILD] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Advanced_Build_Icon>(UI_OBJ_ICON, 715.f, 570.f);

		m_vecUnitIcon[ICON_MOVE]->SetDrawID(1);
		m_vecUnitIcon[ICON_STOP]->SetDrawID(1);
		m_vecUnitIcon[ICON_ATTACK]->SetDrawID(1);
	}
	else if (objId == DYNAMIC_OBJ_MARINE || objId == DYNAMIC_OBJ_FIREBAT || objId == DYNAMIC_OBJ_MEDIC || objId == DYNAMIC_OBJ_TANK)
	{
		m_vecUnitIcon[ICON_MOVE] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Move_Icon>(UI_OBJ_ICON, 655.f, 468.f);
		m_vecUnitIcon[ICON_STOP] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Stop_Icon>(UI_OBJ_ICON, 713.f, 468.f);
		m_vecUnitIcon[ICON_ATTACK] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Attack_Icon>(UI_OBJ_ICON, 768.f, 468.f);

		m_vecUnitIcon[ICON_MOVE]->SetDrawID(1);
		m_vecUnitIcon[ICON_STOP]->SetDrawID(1);
		m_vecUnitIcon[ICON_ATTACK]->SetDrawID(1);
	}
}

void CUIMgr::StaticSetUI(BUILDINGSTATE objId)
{
	if (objId == STATIC_OBJ_CENTER)
	{
		m_vecBuildingIcon[DYANMIC_OBJ_SCV] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_SCV_Icon>(UI_OBJ_ICON, 655.f, 468.f);
	}
	else if (objId == STATIC_OBJ_BARRACK)
	{
		m_vecBuildingIcon[DYNAMIC_OBJ_MARINE] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Marine_Icon>(UI_OBJ_ICON, 655.f, 468.f);
		m_vecBuildingIcon[DYNAMIC_OBJ_FIREBAT] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_FireBat_Icon>(UI_OBJ_ICON, 713.f, 468.f);
		m_vecBuildingIcon[DYNAMIC_OBJ_MEDIC] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Medic_Icon>(UI_OBJ_ICON, 768.f, 468.f);
		m_vecBuildingIcon[DYNAMIC_OBJ_FIREBAT]->SetDrawID(1);
		m_vecBuildingIcon[DYNAMIC_OBJ_MEDIC]->SetDrawID(1);
	}
	else if (objId == STATIC_OBJ_FACTORY)
	{
		m_vecBuildingIcon[DYNAMIC_OBJ_TANK] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Tank_Icon>(UI_OBJ_ICON, 655.f, 468.f);
		m_vecBuildingIcon[DYNAMIC_OBJ_TANK]->SetDrawID(1);
	}
}
