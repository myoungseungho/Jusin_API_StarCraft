#pragma once
#include "Obj_Dynamic.h"
class CGhost :
    public CObj_Dynamic
{
public:
	CGhost();
	virtual ~CGhost();

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
};

