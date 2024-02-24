#pragma once
#include "Obj_Dynamic.h"
class CUnitControlMgr
{
private:
	CUnitControlMgr();
	~CUnitControlMgr();
public:
	static		CUnitControlMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CUnitControlMgr;

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

	void Set_Add_Unit(CObj_Dynamic*);
	void Set_Clear_Unit();
	vector<CObj_Dynamic*>& GetVecUnit() { return m_vecUnit; };

private:
	static CUnitControlMgr* m_pInstance;
	vector<CObj_Dynamic*> m_vecUnit;
};

