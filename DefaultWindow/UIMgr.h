#pragma once
#include "Define.h"
#include "Obj_UI.h"
#include "Obj_Static.h"
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
	void OnClickUnit(CObj*);
	void OnClickIcon(CObj*);
	void SetClear_IconObj();
	void SetClear_StaticObj();
	void SetClear_CurrentBuilding() { m_CurrentBuilding = UI_STATIC_OBJ_END; };
	void DynamicSetUI(DYNAMIC_OBJID);
	void StaticSetUI(BUILDINGSTATE);

	UI_BUILDINGSTATE GetBuilding() { return m_CurrentBuilding; }
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

	vector<CObj_UI*> m_vecUnitIcon;

	CObj_UI* m_center;
	CObj_UI* m_depot;
	CObj_UI* m_barrack;
	CObj_UI* m_factory;
	CObj_UI* m_starport;

	vector<CObj_UI*> m_vecBuilding;

	UI_BUILDINGSTATE m_CurrentBuilding;

	CObj_UI* m_ScvIcon;
	CObj_UI* m_MarineIcon;
	CObj_UI* m_FireBatIcon;
	CObj_UI* m_MedicIcon;
	CObj_UI* m_TankIcon;

	vector<CObj_UI*> m_vecBuildingIcon;
};

