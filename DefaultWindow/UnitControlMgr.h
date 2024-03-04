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

	void Late_Update();
	void Set_Add_Building(CObj*);
	void Set_Add_Unit(CObj*);
	void Set_Add_Unit(vector<CObj*>);
	void Set_Clear_Unit();
	void Set_Clear_Building() { m_Building = nullptr; };
	vector<CObj*>& GetVecUnitOrBuilding() { return m_vecUnitOrBuilding; };
	CObj* GetBuilding() { return m_Building; };
	void Set_EnemyList(list<CObj_Dynamic*> _list) { m_listEnemy = _list; };
	list<CObj_Dynamic*>* Get_EnemyList() { return &m_listEnemy; };
private:
	static CUnitControlMgr* m_pInstance;
	list<CObj_Dynamic*> m_listEnemy;
	vector<CObj*> m_vecUnitOrBuilding;
	vector<HDC> m_vecHDC[DYNAMIC_OBJ_END];
	CObj* m_Building;
};

