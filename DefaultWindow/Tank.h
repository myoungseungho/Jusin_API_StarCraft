#pragma once
#include "Obj_Dynamic.h"
class CTank :
    public CObj_Dynamic
{
public:
	CTank();
	virtual ~CTank();

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
	virtual void Move_Frame() override;
};

