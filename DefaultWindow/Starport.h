#pragma once
#include "Obj_Static.h"
class CStarport :
    public CObj_Static
{
public:
    CStarport();
    virtual ~CStarport();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
protected:
    virtual void InsertBmpFile() override;
};

