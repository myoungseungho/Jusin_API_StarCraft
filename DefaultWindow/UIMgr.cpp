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

CUIMgr* CUIMgr::m_pInstance = nullptr;

CUIMgr::CUIMgr() :m_MoveIcon(nullptr), m_StopIcon(nullptr), m_AttackIcon(nullptr), m_BuildIcon(nullptr), m_AdvancedbuildIcon(nullptr), m_CenterIcon(nullptr), m_BarrackIcon(nullptr), m_DepotIcon(nullptr), m_FactoryIcon(nullptr), m_StarPortIcon(nullptr)
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

	DYNAMIC_OBJID objId = dynamic_cast<CObj_Dynamic*>(_unit)->GetType();

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
}

void CUIMgr::SetClear()
{
	for (auto iter : m_vecIcon)
	{
		if (iter != nullptr)
			iter->Set_Dead();
	}
}
