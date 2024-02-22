#include "stdafx.h"
#include "StateMgr.h"
#include "Scv_Idle_State.h"
#include "Scv_Walk_State.h"
#include "Scv_Attack_State.h"
#include "Scv_Die_State.h"
#include "Marine_Idle_State.h"
#include "Marine_Walk_State.h"
#include "Marine_Attack_State.h"
#include "Marine_Die_State.h"
#include "FireBat_Idle_State.h"
#include "FireBat_Walk_State.h"
#include "FireBat_Attack_State.h"
#include "FireBat_Die_State.h"
#include "Medic_Idle_State.h"
#include "Medic_Walk_State.h"
#include "Medic_Attack_State.h"
#include "Medic_Die_State.h"
#include "Tank_Idle_State.h"
#include "Tank_Walk_State.h"
#include "Tank_Attack_State.h"
#include "Tank_Die_State.h"

CStateMgr* CStateMgr::m_pInstance = nullptr;

CStateMgr::CStateMgr()
{
}

CStateMgr::~CStateMgr()
{
	Release();
}

void CStateMgr::Initialize()
{
	m_vecObjState[OBJ_SCV].push_back(new CScv_Idle_State);
	m_vecObjState[OBJ_SCV].push_back(new CScv_Walk_State);
	m_vecObjState[OBJ_SCV].push_back(new CScv_Attack_State);
	m_vecObjState[OBJ_SCV].push_back(new CScv_Die_State);

	m_vecObjState[OBJ_MARINE].push_back(new CMarine_Idle_State);
	m_vecObjState[OBJ_MARINE].push_back(new CMarine_Walk_State);
	m_vecObjState[OBJ_MARINE].push_back(new CMarine_Attack_State);
	m_vecObjState[OBJ_MARINE].push_back(new CMarine_Die_State);

	m_vecObjState[OBJ_FIREBAT].push_back(new CFireBat_Idle_State);
	m_vecObjState[OBJ_FIREBAT].push_back(new CFireBat_Walk_State);
	m_vecObjState[OBJ_FIREBAT].push_back(new CFireBat_Attack_State);
	m_vecObjState[OBJ_FIREBAT].push_back(new CFireBat_Die_State);

	m_vecObjState[OBJ_MEDIC].push_back(new CMedic_Idle_State);
	m_vecObjState[OBJ_MEDIC].push_back(new CMedic_Walk_State);
	m_vecObjState[OBJ_MEDIC].push_back(new CMedic_Attack_State);
	m_vecObjState[OBJ_MEDIC].push_back(new CMedic_Die_State);

	m_vecObjState[OBJ_TANK].push_back(new CTank_Idle_State);
	m_vecObjState[OBJ_TANK].push_back(new CTank_Walk_State);
	m_vecObjState[OBJ_TANK].push_back(new CTank_Attack_State);
	m_vecObjState[OBJ_TANK].push_back(new CTank_Die_State);
}

void CStateMgr::Release()
{
	for (size_t i = 0; i < OBJ_END; i++)
	{
		for_each(m_vecObjState[i].begin(), m_vecObjState[i].end(), Safe_Delete<IState*>);
	}
}
