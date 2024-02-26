#pragma once
#include "Obj_UI.h"
class CUI_Depot_Icon :
    public CObj_UI
{
    CUI_Depot_Icon();
    virtual ~CUI_Depot_Icon();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
protected:
    virtual void InsertBmpFile() override;
};

