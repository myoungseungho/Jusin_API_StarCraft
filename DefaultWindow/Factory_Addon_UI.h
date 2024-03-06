#pragma once
#include "Obj_UI.h"
class CFactory_Addon_UI :
    public CObj_UI
{
public:
    CFactory_Addon_UI();
    virtual ~CFactory_Addon_UI();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    virtual void Render(HDC hDC);
    void Release() override;

protected:
    virtual void InsertBmpFile() override;

    // CObj_UI��(��) ���� ��ӵ�
    UIOBJECTTYPE GetType() const override;
    int GetDetailType() const override;
};

