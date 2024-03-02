#include "stdafx.h"
#include "UnitControlMgr.h"
#include "UIMgr.h"
CUnitControlMgr* CUnitControlMgr::m_pInstance = nullptr;

CUnitControlMgr::CUnitControlMgr() : m_Building(nullptr)
{
}

CUnitControlMgr::~CUnitControlMgr()
{
}

void CUnitControlMgr::Late_Update()
{
	bool isChange = false;
	for (auto iter = m_vecUnitOrBuilding.begin(); iter != m_vecUnitOrBuilding.end();)
	{
		if (*iter == nullptr || (*iter)->Get_Dead())
		{
			iter=m_vecUnitOrBuilding.erase(iter);
			isChange = true;
		}
		else
		{
			iter++;
		}
	}

	if (isChange)
	{
		CUIMgr::Get_Instance()->OnDragObj();
	}
}


void CUnitControlMgr::Set_Add_Building(CObj* _building)
{
	m_vecUnitOrBuilding.push_back(_building);
	m_Building = _building;
}

void CUnitControlMgr::Set_Add_Unit(CObj* _unit)
{
	CObj_Dynamic* pDynamicObj = dynamic_cast<CObj_Dynamic*>(_unit);
	if (pDynamicObj != nullptr)
	{
		m_vecUnitOrBuilding.push_back(pDynamicObj);
	}
}

void CUnitControlMgr::Set_Add_Unit(vector<CObj*> _vec)
{
	int ivecNumber = 0;
	for (auto& iter : _vec)
	{
		CObj_Dynamic* pDynamicObj = dynamic_cast<CObj_Dynamic*>(iter);

		if (pDynamicObj != nullptr)
		{
			if (ivecNumber >= 12)
				return;

			m_vecUnitOrBuilding.push_back(pDynamicObj);
			ivecNumber++;
		}
	}
}

void CUnitControlMgr::Set_Clear_Unit()
{
	m_vecUnitOrBuilding.clear();
}
