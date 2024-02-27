#pragma once
#include "Obj_Static.h"
class CCenter :
    public CObj_Static
{
public:
    CCenter();
    virtual ~CCenter();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
protected:
    virtual void InsertBmpFile() override;

    // CObj_Static��(��) ���� ��ӵ�
    BUILDINGSTATE GetType() const override;
};

