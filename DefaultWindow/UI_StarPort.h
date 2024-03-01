#pragma once
#include "Obj_UI.h"
class CUI_StarPort_Icon :
    public CObj_UI
{
public:
    CUI_StarPort_Icon();
    virtual ~CUI_StarPort_Icon();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
protected:
    virtual void InsertBmpFile() override;

    // CObj_UI��(��) ���� ��ӵ�
    UIOBJECTTYPE GetType() const override;
    int GetDetailType() const override;
};

