#pragma once
#include "Obj_UI.h"
class CUI_Science_Facility_Icon :
    public CObj_UI
{
public:
    CUI_Science_Facility_Icon();
    virtual ~CUI_Science_Facility_Icon();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
protected:
    virtual void InsertBmpFile() override;
    UIOBJECTTYPE GetType() const override;
    int GetDetailType() const override;
};

