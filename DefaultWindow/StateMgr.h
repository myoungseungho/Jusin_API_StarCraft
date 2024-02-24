#pragma once
#include "State.h"
#include "IdleState.h"
#include "WalkState.h"
#include "AttackState.h"
#include "DieState.h"
class CStateMgr
{
private:
	CStateMgr();
	~CStateMgr();
public:
	static		CStateMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CStateMgr;

		return m_pInstance;
	}

	static void	Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
	void		Initialize();
	void		Release();

	IState* GetState(DYNAMIC_OBJID _Id, STATEID _sId) { return m_vecObjState[_Id][_sId]; };
private:
	static CStateMgr* m_pInstance;

	vector<IState*> m_vecObjState[DYNAMIC_OBJ_END];
};

