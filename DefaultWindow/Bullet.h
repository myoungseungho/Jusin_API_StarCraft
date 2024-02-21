#pragma once
#include "Obj.h"
#include "Obj_Dynamic.h"
class CBullet :	public CObj_Dynamic
{
public:
	CBullet();
	virtual ~CBullet();

public:
	virtual void Initialize() override;
	virtual int  Update() override;
	virtual void Late_Update()override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

