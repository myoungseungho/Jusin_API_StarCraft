#pragma once
#include "Obj_UI.h"
class CMouse :	public CObj_UI
{
public:
	CMouse();
	virtual ~CMouse();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	bool m_bHasSelectUnit;

	// CObj_UI을(를) 통해 상속됨
	ICONSTATE GetType() const override;
};

