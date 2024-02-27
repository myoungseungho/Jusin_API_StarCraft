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
private:
	static CTechTreeMgr* m_pInstance;

	int m_BuildNum = 5;
	vector<BUILDINGSTATE> m_vecPossibleBuilding;
};

