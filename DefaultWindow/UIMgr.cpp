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
CUIMgr* CUIMgr::m_pInstance = nullptr;

CUIMgr::CUIMgr() :m_MoveIcon(nullptr), m_StopIcon(nullptr), m_AttackIcon(nullptr), m_BuildIcon(nullptr)
, m_AdvancedbuildIcon(nullptr), m_CenterIcon(nullptr), m_BarrackIcon(nullptr), m_DepotIcon(nullptr), m_FactoryIcon(nullptr), m_StarPortIcon(nullptr),
m_center(nullptr), m_depot(nullptr), m_barrack(nullptr), m_factory(nullptr), m_starport(nullptr), m_bBuildIng(false)
{

}

CUIMgr::~CUIMgr()
{
}

void CUIMgr::Initialize()
{
	m_vecIcon.push_back(m_MoveIcon);
	m_vecIcon.push_back(m_StopIcon);
	m_vecIcon.push_back(m_AttackIcon);
	m_vecIcon.push_back(m_BuildIcon);
	m_vecIcon.push_back(m_AdvancedbuildIcon);
	m_vecIcon.push_back(m_CenterIcon);
	m_vecIcon.push_back(m_BarrackIcon);
	m_vecIcon.push_back(m_DepotIcon);
	m_vecIcon.push_back(m_FactoryIcon);
	m_vecIcon.push_back(m_StarPortIcon);

	m_vecBuiding.push_back(m_center);
	m_vecBuiding.push_back(m_depot);
	m_vecBuiding.push_back(m_barrack);
	m_vecBuiding.push_back(m_factory);
	m_vecBuiding.push_back(m_starport);
}

void CUIMgr::Render(HDC hDC)
{

}

void CUIMgr::Release()
{

}

void CUIMgr::SetUI(CObj* _unit)
{
	SetClear();

	CObj_Dynamic* dynamic_unit = dynamic_cast<CObj_Dynamic*>(_unit);
	if (dynamic_unit != nullptr)
	{
		DynamicSetUI(dynamic_unit->GetType());
	}
	else
	{
		CObj_Static* static_unit = dynamic_cast<CObj_Static*>(_unit);
		if (static_unit != nullptr)
			StaticSetUI(static_unit->GetType());
	}
}

void CUIMgr::Set_SCV_UI(CObj* _unit)
{
	SetClear();

	ICONSTATE ICONId = dynamic_cast<CObj_UI*>(_unit)->GetType();

	if (ICONId == ICON_BUILD)
	{
		m_vecIcon[ICON_CENTER] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Center_Icon>(UI_OBJ_ICON, 655.f, 468.f);
		m_vecIcon[ICON_DEPOT] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Depot_Icon>(UI_OBJ_ICON, 713.f, 468.f);
		m_vecIcon[ICON_BARRACK] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Barrack_Icon>(UI_OBJ_ICON, 655.f, 518.f);
	}
	else if (ICONId == ICON_ADVANCED_BUILD)
	{
		m_vecIcon[ICON_FACTORY] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Factory_Icon>(UI_OBJ_ICON, 655.f, 468.f);
		m_vecIcon[ICON_STARPORT] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_StarPort_Icon>(UI_OBJ_ICON, 655.f, 518.f);
	}
	else if (ICONId == ICON_CENTER)
	{
		m_vecBuiding[STATIC_OBJ_CENTER] = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CCenter>(STATIC_OBJ_CENTER, FACTION_ALLY, 0.f, 0.f);
		m_vecBuiding[STATIC_OBJ_CENTER]->SetUIBuiding(true);
		m_bBuildIng = true;
	}
	else if (ICONId == ICON_DEPOT)
	{
		m_vecBuiding[STATIC_OBJ_DEPOT] = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CSupplyDepot>(STATIC_OBJ_DEPOT, FACTION_ALLY, 0.f, 0.f);
		m_vecBuiding[STATIC_OBJ_DEPOT]->SetUIBuiding(true);
		m_bBuildIng = true;
	}
	else if (ICONId == ICON_BARRACK)
	{
		m_vecBuiding[STATIC_OBJ_BARRACK] = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CBarrack>(STATIC_OBJ_BARRACK, FACTION_ALLY, 0.f, 0.f);
		m_vecBuiding[STATIC_OBJ_BARRACK]->SetUIBuiding(true);
		m_bBuildIng = true;
	}
	else if (ICONId == ICON_FACTORY)
	{
		m_vecBuiding[STATIC_OBJ_FACTORY] = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CFactory>(STATIC_OBJ_FACTORY, FACTION_ALLY, 0.f, 0.f);
		m_vecBuiding[STATIC_OBJ_FACTORY]->SetUIBuiding(true);
		m_bBuildIng = true;
	}
	else if (ICONId == ICON_STARPORT)
	{
		m_vecBuiding[STATIC_OBJ_STARPORT] = CSpawnMgr::Get_Instance()->Spawn_StaticObj<CStarport>(STATIC_OBJ_STARPORT, FACTION_ALLY, 0.f, 0.f);
		m_vecBuiding[STATIC_OBJ_STARPORT]->SetUIBuiding(true);
		m_bBuildIng = true;
	}
}

void CUIMgr::SetClear()
{
	for (auto iter : m_vecIcon)
	{
		if (iter != nullptr)
			iter->Set_Dead();
	}

	for (auto iter : m_vecBuiding)
	{
		if (iter != nullptr)
			iter->Set_Dead();
	}
}

void CUIMgr::DynamicSetUI(DYNAMIC_OBJID objId)
{
	if (objId == DYANMIC_OBJ_SCV)
	{
		m_vecIcon[ICON_MOVE] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Move_Icon>(UI_OBJ_ICON, 655.f, 468.f);
		m_vecIcon[ICON_STOP] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Stop_Icon>(UI_OBJ_ICON, 713.f, 468.f);
		m_vecIcon[ICON_ATTACK] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Attack_Icon>(UI_OBJ_ICON, 768.f, 468.f);
		m_vecIcon[ICON_BUILD] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Build_Icon>(UI_OBJ_ICON, 655.f, 570.f);
		m_vecIcon[ICON_ADVANCED_BUILD] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Advanced_Build_Icon>(UI_OBJ_ICON, 715.f, 570.f);
	}
	else if (objId == DYNAMIC_OBJ_MARINE || objId == DYNAMIC_OBJ_FIREBAT || objId == DYNAMIC_OBJ_MEDIC || objId == DYNAMIC_OBJ_TANK)
	{
		m_vecIcon[ICON_MOVE] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Move_Icon>(UI_OBJ_ICON, 655.f, 468.f);
		m_vecIcon[ICON_STOP] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Stop_Icon>(UI_OBJ_ICON, 713.f, 468.f);
		m_vecIcon[ICON_ATTACK] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Attack_Icon>(UI_OBJ_ICON, 768.f, 468.f);
	}
}

void CUIMgr::StaticSetUI(BUILDINGSTATE objId)
{

}
