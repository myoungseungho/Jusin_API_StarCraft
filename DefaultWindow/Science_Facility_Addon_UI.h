#pragma once
#include "Obj_UI.h"
class CScience_Facility_Addon_UI :
    public CObj_UI
{
public:
    CScience_Facility_Addon_UI();
    virtual ~CScience_Facility_Addon_UI();
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

