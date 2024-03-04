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
#include "UnitControlMgr.h"
#include "UI_SiegeTank_Wire_Big.h"
#include "UI_STank_Wire_Small.h"
CUI_WireMgr::CUI_WireMgr()
{
}

CUI_WireMgr::~CUI_WireMgr()
{
}

void CUI_WireMgr::Initialize()
{

}

void CUI_WireMgr::Late_Update()
{
	SmallWire_Late_Update();
}

void CUI_WireMgr::OnClickObj(CObj* _unit)
{
	SetClear_BigWireObj();

	CObj_Dynamic* dynamic_unit = dynamic_cast<CObj_Dynamic*>(_unit);
	CObj_Static* staticObj = dynamic_cast<CObj_Static*>(_unit);

	if (dynamic_unit != nullptr)
	{
		DynamicSetUI(dynamic_unit);
		return;
	}

	if (staticObj != nullptr)
	{
		StaticSetUI(staticObj->GetType());
		return;
	}
}

void CUI_WireMgr::OnDragObj()
{
	//유닛이 하나라도 죽으면 모든 아이콘을 삭제하고
	SetClear_SmallWireObj();
	SetClear_BigWireObj();
	//다시 가져옴.
	m_vecUnitCopy = CUnitControlMgr::Get_Instance()->GetVecUnitOrBuilding();

	if (m_vecUnitCopy.size() > 1)
	{
		for (size_t i = 0; i < m_vecUnitCopy.size(); i++)
		{
			float fX = 250.f;
			float fY = 520.f;

			if (i <= 5)
			{
				fX = fX + i * 40;
			}
			else if (i > 5)
			{
				fX = fX + (i - 6) * 40;
				fY = 555.f;
			}

			int grade = m_vecUnitCopy[i]->Get_Stat().m_MaxHp / 6;
			int currentGrade = m_vecUnitCopy[i]->Get_Stat().m_Hp / grade;
			int frame = currentGrade == 0 ? 5 : currentGrade == 1 ? 5 : currentGrade == 2 ? 4 : currentGrade == 3 ? 3
				: currentGrade == 4 ? 2 : currentGrade == 5 ? 1 : currentGrade == 6 ? 0 : 0;

			switch (dynamic_cast<CObj_Dynamic*>(m_vecUnitCopy[i])->GetType())
			{
			case DYNAMIC_OBJ_SCV:
				m_vecSmallWire.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_SCV_Wire_Small>(UI_OBJECT_WIRE, fX, fY));
				break;
			case DYNAMIC_OBJ_MARINE:
				m_vecSmallWire.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Marine_Wire_Small>(UI_OBJECT_WIRE, fX, fY));
				break;
			case DYNAMIC_OBJ_FIREBAT:
				m_vecSmallWire.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_FireBat_Wire_Small>(UI_OBJECT_WIRE, fX, fY));
				break;
			case DYNAMIC_OBJ_MEDIC:
				m_vecSmallWire.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Medic_Wire_Small>(UI_OBJECT_WIRE, fX, fY));
				break;
			case DYNAMIC_OBJ_TANK:
				if (dynamic_cast<CObj_Dynamic*>(m_vecUnitCopy[i])->GetStateID() == SIEGEMODE_STATE)
				{
					m_vecSmallWire.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_STank_Wire_Small>(UI_OBJECT_WIRE, fX, fY));
				}
				else
				{
					m_vecSmallWire.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Tank_Wire_Small>(UI_OBJECT_WIRE, fX, fY));
				}
				break;
			}

			m_vecSmallWire.back()->Get_Frame()->iFrameStart = frame;
		}
	}
}

void CUI_WireMgr::DynamicSetUI(CObj_Dynamic* obj)
{
	int grade = obj->Get_Stat().m_MaxHp / 6;
	int currentGrade = obj->Get_Stat().m_Hp / grade;
	int frame = currentGrade == 0 ? 5 : currentGrade == 1 ? 5 : currentGrade == 2 ? 4 : currentGrade == 3 ? 3
		: currentGrade == 4 ? 2 : currentGrade == 5 ? 1 : currentGrade == 6 ? 0 : 0;

	switch (obj->GetType())
	{
	case DYNAMIC_OBJ_SCV:
		m_vecBigWire.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_SCV_Wire_Big>(UI_OBJECT_WIRE, 250.f, 530.f));
		m_vecBigWire.back()->Get_Frame()->iFrameStart = frame;
		break;
	case DYNAMIC_OBJ_MARINE:
		m_vecBigWire.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Marine_Wire_Big>(UI_OBJECT_WIRE, 250.f, 530.f));
		m_vecBigWire.back()->Get_Frame()->iFrameStart = frame;
		break;
	case DYNAMIC_OBJ_FIREBAT:
		m_vecBigWire.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_FireBat_Wire_Big>(UI_OBJECT_WIRE, 250.f, 530.f));
		m_vecBigWire.back()->Get_Frame()->iFrameStart = frame;
		break;
	case DYNAMIC_OBJ_MEDIC:
		m_vecBigWire.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Medic_Wire_Big>(UI_OBJECT_WIRE, 250.f, 530.f));
		m_vecBigWire.back()->Get_Frame()->iFrameStart = frame;
		break;
	case DYNAMIC_OBJ_TANK:
		if (obj->GetStateID() == SIEGEMODE_STATE)
		{
			m_vecBigWire.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_SiegeTank_Wire_Big>(UI_OBJECT_WIRE, 250.f, 530.f));
			m_vecBigWire.back()->Get_Frame()->iFrameStart = frame;
		}
		else
		{
			m_vecBigWire.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Tank_Wire_Big>(UI_OBJECT_WIRE, 250.f, 530.f));
			m_vecBigWire.back()->Get_Frame()->iFrameStart = frame;
		}
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
		m_vecBigWire.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Center_Wire>(UI_OBJECT_WIRE, 260.f, 530.f));
		break;
	case STATIC_OBJ_DEPOT:
		m_vecBigWire.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Depot_Wire>(UI_OBJECT_WIRE, 260.f, 530.f));
		break;
	case STATIC_OBJ_BARRACK:
		m_vecBigWire.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Barrack_Wire>(UI_OBJECT_WIRE, 260.f, 530.f));
		break;
	case STATIC_OBJ_FACTORY:
		m_vecBigWire.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Factory_Wire>(UI_OBJECT_WIRE, 260.f, 530.f));
		break;
	case STATIC_OBJ_STARPORT:
		m_vecBigWire.push_back(CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_StarPort_Wire>(UI_OBJECT_WIRE, 260.f, 530.f));
		break;
	}
}

void CUI_WireMgr::SetClear_BigWireObj()
{
	for (auto iter : m_vecBigWire)
	{
		if (iter == nullptr || iter->Get_Dead())
			continue;

		iter->Set_Dead();
	}

	m_vecBigWire.clear();
	m_vecBigWire.shrink_to_fit();
}

void CUI_WireMgr::SetClear_SmallWireObj()
{
	for (auto iter : m_vecSmallWire)
	{
		if (iter == nullptr || iter->Get_Dead())
			continue;

		iter->Set_Dead();
	}

	m_vecSmallWire.clear();
	m_vecSmallWire.shrink_to_fit();
}

void CUI_WireMgr::SmallWire_Late_Update()
{
	//다시 가져옴.
	m_vecUnitCopy = CUnitControlMgr::Get_Instance()->GetVecUnitOrBuilding();

	if (m_vecUnitCopy.size() <= 1)
		return;

	for (auto iter : m_vecUnitCopy)
	{
		if (iter == nullptr || iter->Get_Dead() || dynamic_cast<CObj_Static*>(iter) != nullptr)
			return;
	}

	for (int i = 0; i < m_vecUnitCopy.size(); i++)
	{
		int grade = m_vecUnitCopy[i]->Get_Stat().m_MaxHp / 6;
		int currentGrade = m_vecUnitCopy[i]->Get_Stat().m_Hp / grade;
		int frame = currentGrade == 0 ? 5 : currentGrade == 1 ? 5 : currentGrade == 2 ? 4 : currentGrade == 3 ? 3
			: currentGrade == 4 ? 2 : currentGrade == 5 ? 1 : currentGrade == 6 ? 0 : 0;

		m_vecSmallWire[i]->Get_Frame()->iFrameStart = frame;
	}
}
