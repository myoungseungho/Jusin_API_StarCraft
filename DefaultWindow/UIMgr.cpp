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

CUIMgr::CUIMgr() :m_UI_IconMgr(nullptr), m_UI_WireMgr(nullptr), m_UI_TextMgr(nullptr)
{
}

CUIMgr::~CUIMgr()
{
	Release();
}

void CUIMgr::Initialize()
{
	if (m_UI_IconMgr == nullptr)
	{
		m_UI_IconMgr = new CUI_IconMgr;
		m_UI_IconMgr->Initialize();
	}

	if (m_UI_WireMgr == nullptr)
	{
		m_UI_WireMgr = new CUI_WireMgr;
		m_UI_WireMgr->Initialize();
	}

	if (m_UI_TextMgr == nullptr)
	{
		m_UI_TextMgr = new CUI_Text_Mgr;
		m_UI_TextMgr->Initialize();
	}
}

void CUIMgr::Late_Update()
{
	m_UI_WireMgr->Late_Update();
}


void CUIMgr::Render(HDC hDC)
{
	m_UI_TextMgr->Render(hDC);
}

void CUIMgr::Release()
{
	Safe_Delete<CUI_IconMgr*>(m_UI_IconMgr);
	Safe_Delete<CUI_WireMgr*>(m_UI_WireMgr);
	Safe_Delete<CUI_Text_Mgr*>(m_UI_TextMgr);
}

void CUIMgr::OnClickObj(CObj* _unit)
{
	m_UI_IconMgr->OnClickObj(_unit);
	m_UI_WireMgr->OnClickObj(_unit);
	m_UI_TextMgr->OnClickObj(_unit);
}

void CUIMgr::OnClickIcon(CObj* _unit)
{
	m_UI_IconMgr->OnClickIcon(_unit);
}

void CUIMgr::OnDragObj()
{
	m_UI_WireMgr->OnDragObj();
}

void CUIMgr::SetClear_Dynamic_Obj()
{
	m_UI_IconMgr->SetClear_IconObj();
	m_UI_WireMgr->SetClear_BigWireObj();
	m_UI_WireMgr->SetClear_SmallWireObj();
	m_UI_TextMgr->SetClear_Text();
}

void CUIMgr::SetClear_StaticObj()
{
	m_UI_IconMgr->SetClear_StaticObj();
}

void CUIMgr::DynamicSetUI(DYNAMIC_OBJID objId)
{
	m_UI_IconMgr->DynamicSetUI(objId);
}

void CUIMgr::StaticSetUI(BUILDINGSTATE objId)
{
	m_UI_IconMgr->StaticSetUI(objId);
}
