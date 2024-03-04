#include "stdafx.h"
#include "EconomyMgr.h"
CEconomyMgr* CEconomyMgr::m_pInstance = nullptr;

CEconomyMgr::CEconomyMgr()
{
	m_Resource.m_Mineral = 10000;
	m_Resource.m_Gas = 10000;
	m_Resource.m_People = 136;
	m_Resource.m_MaxPeople = 200;
}

CEconomyMgr::~CEconomyMgr()
{
}

void CEconomyMgr::Initialize()
{
}
