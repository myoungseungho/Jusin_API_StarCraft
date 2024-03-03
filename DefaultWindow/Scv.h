#pragma once
#include "Obj_Dynamic.h"
#include "State.h"
#include "Obj_UI.h"
class CScv : public CObj_Dynamic
{
public:
	CScv();
	virtual ~CScv();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

protected:
	virtual void InsertBmpFile() override;

private:
	DYNAMIC_OBJID GetType() const override;

};

