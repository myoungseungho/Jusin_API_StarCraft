#include "stdafx.h"
#include "UnitControlMgr.h"

CUnitControlMgr* CUnitControlMgr::m_pInstance = nullptr;

CUnitControlMgr::CUnitControlMgr()
{
}

CUnitControlMgr::~CUnitControlMgr()
{
}

void CUnitControlMgr::Set_Add_Unit(CObj_Dynamic* _unit)
{
	m_vecUnit.push_back(_unit);
}

void CUnitControlMgr::Set_Clear_Unit()
{
	m_vecUnit.clear();
}
