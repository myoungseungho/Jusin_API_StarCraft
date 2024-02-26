#pragma once
#include "Obj_Static.h"
class CBarrack :
    public CObj_Static
{
public:
    CBarrack();
    virtual ~CBarrack();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
protected:
    virtual void InsertBmpFile() override;
};

