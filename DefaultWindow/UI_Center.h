#pragma once
#include "Obj_UI.h"
class CUI_Center_Icon :
    public CObj_UI
{
public:
    CUI_Center_Icon();
    virtual ~CUI_Center_Icon();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    UIOBJECTTYPE GetType() const override;
    int GetDetailType() const override;
protected:
    virtual void InsertBmpFile() override;
};

