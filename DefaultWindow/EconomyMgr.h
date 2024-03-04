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
private:
	static CEconomyMgr* m_pInstance;
};

