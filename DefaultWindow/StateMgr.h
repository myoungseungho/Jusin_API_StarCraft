#pragma once
#include "State.h"
class CStateMgr
{
public:
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
	vector<IState*>* GetVecObjState(OBJID _Id) { return &m_vecObjState[_Id]; }

private:
	static CStateMgr* m_pInstance;

	vector<IState*> m_vecObjState[OBJ_END];
	vector<IState*> m_vecState;
};

