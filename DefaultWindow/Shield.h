#pragma once
#include "Obj_Dynamic.h"
class CShield :	public CObj_Dynamic
{
public:
	CShield();
	virtual ~CShield();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

