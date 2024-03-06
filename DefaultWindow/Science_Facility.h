#pragma once
#include "Obj_Static.h"
class CScience_Facility :
    public CObj_Static
{
public:
    CScience_Facility();
    virtual ~CScience_Facility();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
public:
    virtual void Spawn_Unit();
protected:
    virtual void InsertBmpFile() override;

    // CObj_Static을(를) 통해 상속됨
    BUILDINGSTATE GetType() const override;
};

