#pragma once
#include "Obj.h"
#include "Obj_UI.h"
#include "Obj_Dynamic.h"
class CUI_WireMgr
{
public:
	CUI_WireMgr();
	~CUI_WireMgr();
public:
	void Initialize();
	void Late_Update();
	void OnClickObj(CObj*);
	void OnDragObj();
public:
	void DynamicSetUI(CObj_Dynamic*);
	void StaticSetUI(BUILDINGSTATE);
	void SetClear_BigWireObj();
	void SetClear_SmallWireObj();
private:
	vector<CObj_UI*> m_vecSmallWire;
	vector<CObj_UI*> m_vecBigWire;

	vector<CObj*> m_vecUnitCopy;
};

