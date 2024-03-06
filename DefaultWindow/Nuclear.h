#pragma once
#include "Obj_Dynamic.h"
class CNuclear :
    public CObj_Dynamic
{
public:
	CNuclear();
	virtual ~CNuclear();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
public:
	DYNAMIC_OBJID GetType() const override;
protected:
	virtual void InsertBmpFile() override;
private:
	bool CheckDestination();
	float m_fInitY;
};

