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
		m_MoveIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Move_Icon>(UI_OBJ_ICON, 655.f, 468.f);
		m_StopIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Stop_Icon>(UI_OBJ_ICON, 713.f, 468.f);
		m_AttackIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Attack_Icon>(UI_OBJ_ICON, 768.f, 468.f);
		m_BuildIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Build_Icon>(UI_OBJ_ICON, 655.f, 570.f);
		m_AdvancedbuildIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Advanced_Build_Icon>(UI_OBJ_ICON, 715.f, 570.f);
	}
	else if (objId == DYNAMIC_OBJ_MARINE || objId == DYNAMIC_OBJ_FIREBAT || objId == DYNAMIC_OBJ_MEDIC || objId == DYNAMIC_OBJ_TANK)
	{
		m_MoveIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Move_Icon>(UI_OBJ_ICON, 655.f, 468.f);
		m_StopIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Stop_Icon>(UI_OBJ_ICON, 713.f, 468.f);
		m_AttackIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Attack_Icon>(UI_OBJ_ICON, 768.f, 468.f);
	}
}

void CUIMgr::Set_SCV_UI(CObj* _unit)
{
	SetClear();

	ICONSTATE ICONId = dynamic_cast<CObj_UI*>(_unit)->GetType();

	if (ICONId == ICON_BUILD)
	{
		m_CenterIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Center_Icon>(UI_OBJ_ICON, 655.f, 468.f);
		m_DepotIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Depot_Icon>(UI_OBJ_ICON, 713.f, 468.f);
		m_BarrackIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Barrack_Icon>(UI_OBJ_ICON, 655.f, 518.f);
	}
	else if (ICONId == ICON_ADVANCED_BUILD)
	{
		m_FactoryIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Factory_Icon>(UI_OBJ_ICON, 655.f, 468.f);
		m_StarPortIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_StarPort_Icon>(UI_OBJ_ICON, 655.f, 518.f);
	}
}

void CUIMgr::SetClear()
{
	if (m_MoveIcon != nullptr)
		m_MoveIcon->Set_Dead();

	if (m_StopIcon != nullptr)
		m_StopIcon->Set_Dead();

	if (m_AttackIcon != nullptr)
		m_AttackIcon->Set_Dead();

	if (m_BuildIcon != nullptr)
		m_BuildIcon->Set_Dead();

	if (m_AdvancedbuildIcon != nullptr)
		m_AdvancedbuildIcon->Set_Dead();

	if (m_CenterIcon != nullptr)
		m_CenterIcon->Set_Dead();

	if (m_DepotIcon != nullptr)
		m_DepotIcon->Set_Dead();

	if (m_BarrackIcon != nullptr)
		m_BarrackIcon->Set_Dead();

	if (m_FactoryIcon != nullptr)
		m_FactoryIcon->Set_Dead();

	if (m_StarPortIcon != nullptr)
		m_StarPortIcon->Set_Dead();
}
