#pragma once
#include "Obj_Static.h"
class CFactory :
	public CObj_Static
{
public:
	CFactory();
	virtual ~CFactory();
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
public:
	virtual void Spawn_Unit(DYNAMIC_OBJID);
protected:
	virtual void InsertBmpFile() override;

	// CObj_Static을(를) 통해 상속됨
	BUILDINGSTATE GetType() const override;
};

