#pragma once
#include "Obj_Dynamic.h"
#include "State.h"
class CFireBat : public CObj_Dynamic
{
public:
	CFireBat();
	virtual ~CFireBat();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

protected:
	virtual void InsertBmpFile() override;

    // CObj_Dynamic을(를) 통해 상속됨
    DYNAMIC_OBJID GetType() const override;
};

