#pragma once
#include "Obj_UI.h"
class CBackGround :
    public CObj_UI
{
public:
    CBackGround();
    virtual ~CBackGround();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    // CObj_UI을(를) 통해 상속됨
    ICONSTATE GetType() const override;
};

