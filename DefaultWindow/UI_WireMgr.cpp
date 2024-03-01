#include "stdafx.h"
#include "UI_WireMgr.h"
#include "Obj_Dynamic.h"
#include "Obj_Static.h"
#include "SpawnMgr.h"
#include "UI_SCV_Wire_Big.h"
#include "UI_SCV_Wire_Small.h"
#include "UI_Marine_Wire_Big.h"
#include "UI_Marine_Wire_Small.h"
#include "UI_FireBat_Wire_Big.h"
#include "UI_FireBat_Wire_Small.h"
#include "UI_Medic_Wire_Big.h"
#include "UI_Medic_Wire_Small.h"
#include "UI_Tank_Wire_Big.h"
#include "UI_Tank_Wire_Small.h"
#include "UI_Center_Wire.h"
#include "UI_Depot_Wire.h"
#include "UI_Barrack_Wire.h"
#include "UI_Factory_Wire.h"
#include "UI_StarPort_Wire.h"
CUI_WireMgr::CUI_WireMgr() :m_Scv_Small_Wire(nullptr), m_Marine_Small_Wire(nullptr), m_FireBat_Small_Wire(nullptr),
m_Medic_Small_Wire(nullptr), m_Tank_Small_Wire(nullptr),
m_Scv_Big_Wire(nullptr), m_Marine_Big_Wire(nullptr), m_FireBat_Big_Wire(nullptr), m_Medic_Big_Wire(nullptr), m_Tank_Big_Wire(nullptr),
m_Center_Big_Wire(nullptr), m_Depot_Big_Wire(nullptr), m_Barrack_Big_Wire(nullptr), m_Factory_Big_Wire(nullptr), m_StarPort_Big_Wire(nullptr)
{
}

CUI_WireMgr::~CUI_WireMgr()
{
}

void CUI_WireMgr::Initialize()
{
	m_vecSmallWire.push_back(m_Scv_Small_Wire);
	m_vecSmallWire.push_back(m_Marine_Small_Wire);
	m_vecSmallWire.push_back(m_FireBat_Small_Wire);
	m_vecSmallWire.push_back(m_Medic_Small_Wire);
	m_vecSmallWire.push_back(m_Tank_Small_Wire);

	m_vecBigWire.push_back(m_Scv_Big_Wire);
	m_vecBigWire.push_back(m_Marine_Big_Wire);
	m_vecBigWire.push_back(m_FireBat_Big_Wire);
	m_vecBigWire.push_back(m_Medic_Big_Wire);
	m_vecBigWire.push_back(m_Tank_Big_Wire);
	m_vecBigWire.push_back(m_Center_Big_Wire);
	m_vecBigWire.push_back(m_Depot_Big_Wire);
	m_vecBigWire.push_back(m_Barrack_Big_Wire);
	m_vecBigWire.push_back(m_Factory_Big_Wire);
	m_vecBigWire.push_back(m_StarPort_Big_Wire);
}

void CUI_WireMgr::OnClickObj(CObj* _unit)
{
	SetClear_BigWireObj();

	CObj_Dynamic* dynamic_unit = dynamic_cast<CObj_Dynamic*>(_unit);
	CObj_Static* staticObj = dynamic_cast<CObj_Static*>(_unit);

	if (dynamic_unit != nullptr)
		DynamicSetUI(dynamic_unit->GetType());

	if (staticObj != nullptr)
		StaticSetUI(staticObj->GetType());
}

void CUI_WireMgr::DynamicSetUI(DYNAMIC_OBJID objId)
{
	switch (objId)
	{
	case DYANMIC_OBJ_SCV:
		//m_vecSmallWire[WIRE_SCV_SMALL] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_SCV_Wire_Small>(UI_OBJECT_WIRE, 400.f, 500.f);
		m_vecBigWire[WIRE_SCV_BIG] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_SCV_Wire_Big>(UI_OBJECT_WIRE, 250.f, 530.f);
		break;
	case DYNAMIC_OBJ_MARINE:
		//m_vecSmallWire[WIRE_MARINE_SMALL] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Marine_Wire_Small>(UI_OBJECT_WIRE, 655.f, 468.f);
		m_vecBigWire[WIRE_MARINE_BIG] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Marine_Wire_Big>(UI_OBJECT_WIRE, 250.f, 530.f);
		break;
	case DYNAMIC_OBJ_FIREBAT:
		//m_vecSmallWire[WIRE_FIREBAT_SMALL] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_FireBat_Wire_Small>(UI_OBJECT_WIRE, 655.f, 468.f);
		m_vecBigWire[WIRE_FIREBAT_BIG] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_FireBat_Wire_Big>(UI_OBJECT_WIRE, 250.f, 530.f);
		break;
	case DYNAMIC_OBJ_MEDIC:
		//m_vecSmallWire[WIRE_MEDIC_SMALL] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Medic_Wire_Small>(UI_OBJECT_WIRE, 655.f, 468.f);
		m_vecBigWire[WIRE_MEDIC_BIG] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Medic_Wire_Big>(UI_OBJECT_WIRE, 250.f, 530.f);
		break;
	case DYNAMIC_OBJ_TANK:
		//m_vecSmallWire[WIRE_TANK_SMALL] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Tank_Wire_Small>(UI_OBJECT_WIRE, 655.f, 468.f);
		m_vecBigWire[WIRE_TANK_BIG] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Tank_Wire_Big>(UI_OBJECT_WIRE, 250.f, 530.f);
		break;
	case DYNAMIC_OBJ_END:
		break;
	default:
		break;
	}
}

void CUI_WireMgr::StaticSetUI(BUILDINGSTATE objId)
{
	switch (objId)
	{
	case STATIC_OBJ_CENTER:
		m_vecBigWire[WIRE_CENTER_BIG] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Center_Wire>(UI_OBJECT_WIRE, 260.f, 530.f);
		break;
	case STATIC_OBJ_DEPOT:
		m_vecBigWire[WIRE_DEPOT_BIG] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Depot_Wire>(UI_OBJECT_WIRE, 260.f, 530.f);
		break;
	case STATIC_OBJ_BARRACK:
		m_vecBigWire[WIRE_BARRACK_BIG] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Barrack_Wire>(UI_OBJECT_WIRE, 260.f, 530.f);
		break;
	case STATIC_OBJ_FACTORY:
		m_vecBigWire[WIRE_FACTORY_BIG] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Factory_Wire>(UI_OBJECT_WIRE, 260.f, 530.f);
		break;
	case STATIC_OBJ_STARPORT:
		m_vecBigWire[WIRE_STARPORT_BIG] = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_StarPort_Wire>(UI_OBJECT_WIRE, 260.f, 530.f);
		break;
	}
}

void CUI_WireMgr::SetClear_BigWireObj()
{
	for (auto iter : m_vecBigWire)
	{
		if (iter != nullptr)
			iter->Set_Dead();
	}
}