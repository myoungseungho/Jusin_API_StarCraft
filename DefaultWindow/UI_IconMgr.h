#pragma once
#include "Obj_UI.h"
#include "Define.h"

class CUI_IconMgr
{
public:
	CUI_IconMgr();
	~CUI_IconMgr();
public:
	void Initialize();
public:
	void OnClickObj(CObj* _unit);
	void OnClickIcon(CObj* _unit);
	void OnDragObj();
	void SetClear_IconObj();
	void SetClear_StaticObj();
	void SetClear_CurrentBuilding() { m_CurrentBuilding = UI_STATIC_OBJ_END; };
	void DynamicSetUI(CObj*);
	void StaticSetUI(BUILDINGSTATE);

	UI_BUILDINGSTATE GetBuilding() { return m_CurrentBuilding; }
	bool GetNuclear() { return m_GhostNuclear; }
private:
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

	bool m_GhostNuclear;
};

