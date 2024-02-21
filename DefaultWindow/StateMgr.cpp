#include "stdafx.h"
#include "StateMgr.h"
#include "Scv_Idle_State.h"
#include "Scv_Walk_State.h"
#include "Scv_Attack_State.h"

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
}

void CStateMgr::Release()
{
	for_each(m_vecState.begin(), m_vecState.end(), Safe_Delete<IState*>);
}
