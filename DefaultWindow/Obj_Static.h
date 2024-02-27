#pragma once
#include "Obj.h"
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

public:
	void SetObstcale();
	void SetUIBuiding(bool _isBuilding) { m_UIBuilding = _isBuilding; }
public:
	bool m_IsInfoUpdate;
	bool m_UIBuilding;
};

