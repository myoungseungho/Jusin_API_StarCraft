#pragma once
#include "Obj_Static.h"
class CSupplyDepot :
    public CObj_Static
{
public:
    CSupplyDepot();
    virtual ~CSupplyDepot();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
protected:
    virtual void InsertBmpFile() override;

    // CObj_Static을(를) 통해 상속됨
    BUILDINGSTATE GetType() const override;
};

