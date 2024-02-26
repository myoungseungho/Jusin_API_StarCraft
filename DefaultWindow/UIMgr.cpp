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

CUIMgr::CUIMgr()
{
}

CUIMgr::~CUIMgr()
{
}

void CUIMgr::Initialize()
{
	CObj_UI* moveIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Move_Icon>(UI_OBJ_ICON, 655.f, 468.f);
	CObj_UI* stopIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Stop_Icon>(UI_OBJ_ICON, 713.f, 468.f);
	CObj_UI* attackIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Attack_Icon>(UI_OBJ_ICON, 768.f, 468.f);
	CObj_UI* buildIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Build_Icon>(UI_OBJ_ICON, 655.f, 570.f);
	CObj_UI* advancedbuildIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Advanced_Build_Icon>(UI_OBJ_ICON, 715.f, 570.f);

	CObj_UI* centerIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Center_Icon>(UI_OBJ_ICON, 655.f, 468.f);
	CObj_UI* depotIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Depot_Icon>(UI_OBJ_ICON, 713.f, 468.f);
	CObj_UI* barrackIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Barrack_Icon>(UI_OBJ_ICON, 655.f, 519.f);
	CObj_UI* factoryIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Factory_Icon>(UI_OBJ_ICON, 655.f, 468.f);
	CObj_UI* starportIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_StarPort_Icon>(UI_OBJ_ICON, 655.f, 519.f);


	m_vecUnitUI[DYANMIC_OBJ_SCV].push_back(moveIcon);
	m_vecUnitUI[DYANMIC_OBJ_SCV].push_back(stopIcon);
	m_vecUnitUI[DYANMIC_OBJ_SCV].push_back(attackIcon);
	m_vecUnitUI[DYANMIC_OBJ_SCV].push_back(buildIcon);
	m_vecUnitUI[DYANMIC_OBJ_SCV].push_back(advancedbuildIcon);

	m_vecUnitUI[DYNAMIC_OBJ_MARINE].push_back(moveIcon);
	m_vecUnitUI[DYNAMIC_OBJ_MARINE].push_back(stopIcon);
	m_vecUnitUI[DYNAMIC_OBJ_MARINE].push_back(attackIcon);
}

void CUIMgr::Render(HDC hDC)
{
	vector<CObj_Dynamic*> vecUnit = CUnitControlMgr::Get_Instance()->GetVecUnit();

	if (vecUnit.size() == 0)
		return;

	for (auto iter : m_vecUnitUI[vecUnit.back()->GetType()])
	{
		iter->Render(hDC);
	}
}

void CUIMgr::Release()
{
	for (size_t i = 0; i < DYNAMIC_OBJ_END; i++)
	{
		for_each(m_vecUnitUI[i].begin(), m_vecUnitUI[i].end(), Safe_Delete<CObj_UI*>);
	}
}
