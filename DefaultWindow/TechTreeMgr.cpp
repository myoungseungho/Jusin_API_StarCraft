#include "stdafx.h"
#include "TechTreeMgr.h"


CTechTreeMgr* CTechTreeMgr::m_pInstance = nullptr;

CTechTreeMgr::CTechTreeMgr() : m_bIsAcademy(false), m_bIsFactory_Addon(false), m_bIsScience_Addon(false)
{
}

CTechTreeMgr::~CTechTreeMgr()
{
}

void CTechTreeMgr::Initialize()
{
	m_vecPossibleBuilding.reserve(m_BuildNum);

	for (size_t i = 0; i <= STATIC_OBJ_BARRACK; i++)
	{
		m_vecPossibleBuilding.push_back((BUILDINGSTATE)i);
	}
}

void CTechTreeMgr::SetBuiding(BUILDINGSTATE _build)
{
	switch (_build)
	{
	case STATIC_OBJ_BARRACK:
		for (auto iter : m_vecPossibleBuilding)
		{
			if (iter == STATIC_OBJ_FACTORY || iter == STATIC_OBJ_ACADENY)
				return;
		}
		m_vecPossibleBuilding.push_back(STATIC_OBJ_ACADENY);
		m_vecPossibleBuilding.push_back(STATIC_OBJ_FACTORY);
		break;

	case STATIC_OBJ_FACTORY:
		for (auto iter : m_vecPossibleBuilding)
		{
			if (iter == STATIC_OBJ_STARPORT)
				return;
		}
		m_vecPossibleBuilding.push_back(STATIC_OBJ_STARPORT);
		m_vecPossibleBuilding.push_back(STATIC_OBJ_FACTORY_ADDON);
		break;

	case STATIC_OBJ_STARPORT:
		for (auto iter : m_vecPossibleBuilding)
		{
			if (iter == STATIC_OBJ_SCIENCE_FACILITY)
				return;
		}
		m_vecPossibleBuilding.push_back(STATIC_OBJ_SCIENCE_FACILITY);
		break;

	case STATIC_OBJ_SCIENCE_FACILITY_ADDON:
		for (auto iter : m_vecPossibleBuilding)
		{
			if (iter == STATIC_OBJ_NUCLEARSILO)
				return;
		}
		m_vecPossibleBuilding.push_back(STATIC_OBJ_NUCLEARSILO);
		break;
	}
}

bool CTechTreeMgr::GetCanBuild(BUILDINGSTATE _state)
{
	for (auto iter : m_vecPossibleBuilding)
	{
		if (iter == _state)
			return true;
	}
	return false;
}

