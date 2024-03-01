#pragma once
#include "Obj.h"
#include "Obj_UI.h"
class CUI_WireMgr
{
public:
	CUI_WireMgr();
	~CUI_WireMgr();
public:
	void Initialize();
	void OnClickObj(CObj*);
public:
	void DynamicSetUI(DYNAMIC_OBJID);
	void StaticSetUI(BUILDINGSTATE);
	void SetClear_BigWireObj();
private:
	CObj_UI* m_Scv_Small_Wire;
	CObj_UI* m_Marine_Small_Wire;
	CObj_UI* m_FireBat_Small_Wire;
	CObj_UI* m_Medic_Small_Wire;
	CObj_UI* m_Tank_Small_Wire;

	CObj_UI* m_Scv_Big_Wire;
	CObj_UI* m_Marine_Big_Wire;
	CObj_UI* m_FireBat_Big_Wire;
	CObj_UI* m_Medic_Big_Wire;
	CObj_UI* m_Tank_Big_Wire;

	vector<CObj_UI*> m_vecSmallWire;
	vector<CObj_UI*> m_vecBigWire;
};

