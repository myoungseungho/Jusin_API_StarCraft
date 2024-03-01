#pragma once
#include "Obj_UI.h"
class CUI_Medic_Wire_Big :
    public CObj_UI
{
public:
    CUI_Medic_Wire_Big();
    virtual ~CUI_Medic_Wire_Big();
public:
    // CObj_UI��(��) ���� ��ӵ�
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    virtual void Render(HDC hDC) override;
    void Release() override;
    UIOBJECTTYPE GetType() const override;
    int GetDetailType() const override;
protected:
    virtual void InsertBmpFile() override;

};

