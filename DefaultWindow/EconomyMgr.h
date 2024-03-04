#pragma once
#include "Define.h"
class CEconomyMgr
{
private:
	CEconomyMgr();
	~CEconomyMgr();

public:
	static CEconomyMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CEconomyMgr;

		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
public:
	void Initialize();

public:
	void SetMineral(int _mineral = 7) { m_Resource.m_Mineral += _mineral; };
	void SetGas(int _gas) { m_Resource.m_Gas += _gas; }
	MINERALGASPEOPLE GetResource() { return m_Resource; }

private:
	static CEconomyMgr* m_pInstance;
	MINERALGASPEOPLE m_Resource;
};

