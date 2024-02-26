#include "stdafx.h"
#include "TechTreeMgr.h"


CTechTreeMgr* CTechTreeMgr::m_pInstance = nullptr;

CTechTreeMgr::CTechTreeMgr()
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
			if (iter == STATIC_OBJ_FACTORY)
				return;
		}
		m_vecPossibleBuilding.push_back(STATIC_OBJ_FACTORY);
		break;
	case STATIC_OBJ_FACTORY:
		for (auto iter : m_vecPossibleBuilding)
		{
			if (iter == STATIC_OBJ_STARPORT)
				return;
		}
		m_vecPossibleBuilding.push_back(STATIC_OBJ_STARPORT);
		break;
	}
}