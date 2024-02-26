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
	void Release();
public:
	void SetUI(CObj*);
	void Set_SCV_UI(CObj*);
	void SetClear();
	
private:
	static CUIMgr* m_pInstance;

	CObj_UI* m_MoveIcon;
	CObj_UI* m_StopIcon;
	CObj_UI* m_AttackIcon;
	CObj_UI* m_BuildIcon;
	CObj_UI* m_AdvancedbuildIcon;

	CObj_UI* m_CenterIcon;
	CObj_UI* m_BarrackIcon;
	CObj_UI* m_DepotIcon;
	CObj_UI* m_FactoryIcon;
	CObj_UI* m_StarPortIcon;

	vector<CObj_UI*> m_vecIcon;
};

