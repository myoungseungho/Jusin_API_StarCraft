#pragma once
#include "Obj_UI.h"
class CBarrack_UI :
    public CObj_UI
{
public:
    CBarrack_UI();
    virtual ~CBarrack_UI();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    virtual void Render(HDC hDC);
    void Release() override;
    ICONSTATE GetType() const override;

protected:
    virtual void InsertBmpFile() override;
};

