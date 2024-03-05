#pragma once
#include "Obj.h"
#include "Define.h"
class CObj_Static :
	public CObj
{
public:
	CObj_Static();
	virtual ~CObj_Static();
public:
	void Initialize() PURE;
	int Update() PURE;
	void Late_Update()PURE;
	void Render(HDC hDC) PURE;
	void Release() PURE;
public:
	virtual BUILDINGSTATE GetType() const PURE;
	virtual void Spawn_Unit(DYNAMIC_OBJID);
	virtual void Move_Frame();
public:
	void SetObstcale();
	void UIBuilding();
	bool GetIsCompleteBuilding() { return m_CompleteBuilding; }
public:
	bool m_UIBuilding;
protected:
	vector<CObj*> m_vecWaitUnit;
	bool m_CompleteBuilding;
};

