#pragma once
#include "Obj_UI.h"
class CUI_Tank_Display :
    public CObj_UI
{
public:
    CUI_Tank_Display();
    virtual ~CUI_Tank_Display();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    // CObj_UI을(를) 통해 상속됨
    UIOBJECTTYPE GetType() const override;
    int GetDetailType() const override;
};

