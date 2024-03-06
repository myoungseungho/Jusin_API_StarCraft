#pragma once
#include "Define.h"



class CTechTreeMgr
{
private:
	CTechTreeMgr();
	~CTechTreeMgr();
public:
	static		CTechTreeMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CTechTreeMgr;

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
public:
	void Initialize();
	void SetBuiding(BUILDINGSTATE _build);
	bool GetCanBuild(BUILDINGSTATE);
	void SetIsAcademy() { m_bIsAcademy = true; }
	bool GetIsAcademy() { return m_bIsAcademy; }
	void SetIsFactory_Addon() { m_bIsFactory_Addon = true; }
	bool GetIsFactory_Addon() { return m_bIsFactory_Addon; }
	void SetIsScience_Addon() { m_bIsScience_Addon = true; }
	bool GetIsScience_Addon() { return m_bIsScience_Addon; }
private:
	static CTechTreeMgr* m_pInstance;

	int m_BuildNum = 5;
	vector<BUILDINGSTATE> m_vecPossibleBuilding;

	bool m_bIsAcademy;
	bool m_bIsFactory_Addon;
	bool m_bIsScience_Addon;
};

