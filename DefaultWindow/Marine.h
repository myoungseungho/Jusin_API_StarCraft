#pragma once
#include "Obj_Dynamic.h"
class CMarine : public CObj_Dynamic
{
public:
    CMarine();
    virtual ~CMarine();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
public:
    virtual void InsertBmpFile();

    // CObj_Dynamic을(를) 통해 상속됨
    DYNAMIC_OBJID GetType() const override;
};

