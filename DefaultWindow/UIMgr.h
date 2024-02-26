#pragma once
#include "Define.h"
#include "Obj_UI.h"
class CUIMgr
{
private:
	CUIMgr();
	~CUIMgr();
public:
	static		CUIMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CUIMgr;

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
	void Render(HDC hDC);
//public:
//	void Set_UI(CObj_UI*);
//	void Init_VecUI();
private:
	static CUIMgr* m_pInstance;
	vector<CObj_UI*> m_vecUnitUI[DYNAMIC_OBJ_END];

	vector<HDC> m_vecUI;
};

