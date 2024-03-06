#pragma once
#include "Obj_Static.h"
class CFactory_Addon :
    public CObj_Static
{
public:
    CFactory_Addon();
    virtual ~CFactory_Addon();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
public:
    virtual void Spawn_Unit();
protected:
    virtual void InsertBmpFile() override;

    // CObj_Static��(��) ���� ��ӵ�
    BUILDINGSTATE GetType() const override;
};

