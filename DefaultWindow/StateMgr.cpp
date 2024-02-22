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
}

void CStateMgr::Release()
{
	for_each(m_vecState.begin(), m_vecState.end(), Safe_Delete<IState*>);
}
