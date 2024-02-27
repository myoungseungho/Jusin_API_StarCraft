#pragma once
#include "Obj_UI.h"
class CUI_Medic_Icon :
    public CObj_UI
{
public:
    CUI_Medic_Icon();
    virtual ~CUI_Medic_Icon();
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


