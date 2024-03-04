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
	void SetMineral() { m_Resource.m_Mineral += 7; };
	MINERALGASPEOPLE GetResource() { return m_Resource; }

private:
	static CEconomyMgr* m_pInstance;
	MINERALGASPEOPLE m_Resource;
};

