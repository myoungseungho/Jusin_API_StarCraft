#pragma once
#include "Obj_Dynamic.h"
class CNuclear_Effect :
    public CObj_Dynamic
{
public:
    CNuclear_Effect();
    virtual ~CNuclear_Effect();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    DYNAMIC_OBJID GetType() const override;
protected:
    virtual void InsertBmpFile() override;
};

