#include "stdafx.h"
#include "UnitControlMgr.h"

CUnitControlMgr* CUnitControlMgr::m_pInstance = nullptr;

CUnitControlMgr::CUnitControlMgr() : m_Building(nullptr)
{
}

CUnitControlMgr::~CUnitControlMgr()
{
}

void CUnitControlMgr::Set_Add_Building(CObj* _building)
{
	m_Building = _building;
}

void CUnitControlMgr::Set_Add_Unit(CObj* _unit)
{
	CObj_Dynamic* pDynamicObj = dynamic_cast<CObj_Dynamic*>(_unit);
	if (pDynamicObj != nullptr)
	{
		m_vecUnit.push_back(pDynamicObj);
	}
}

void CUnitControlMgr::Set_Add_Unit(vector<CObj*> _vec)
{
	for (auto& iter : _vec)
	{
		CObj_Dynamic* pDynamicObj = dynamic_cast<CObj_Dynamic*>(iter);

		if (pDynamicObj != nullptr)
			m_vecUnit.push_back(pDynamicObj);
	}
}

void CUnitControlMgr::Set_Clear_Unit()
{
	m_vecUnit.clear();
}
