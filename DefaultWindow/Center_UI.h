#pragma once
#include "Obj_UI.h"
class CCenter_UI :
    public CObj_UI
{
public:
    CCenter_UI();
    virtual ~CCenter_UI();
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

