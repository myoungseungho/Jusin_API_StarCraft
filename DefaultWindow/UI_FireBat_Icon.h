#pragma once
#include "Obj_UI.h"
class CUI_FireBat_Icon :
    public CObj_UI
{
public:
    CUI_FireBat_Icon();
    virtual ~CUI_FireBat_Icon();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
protected:
    virtual void InsertBmpFile() override;

    // CObj_UI��(��) ���� ��ӵ�
    ICONSTATE GetType() const override;
};

