#pragma once
#include "State.h"
class CMarine_Walk_State :
    public IState
{
public:
    CMarine_Walk_State();
    virtual ~CMarine_Walk_State();
public:
    void Initialize(CObj_Dynamic*) override;
    int Update(CObj_Dynamic*) override;
    void Late_Update(CObj_Dynamic*) override;
    void Render(CObj_Dynamic*, HDC hDC) override;
    void Release(CObj_Dynamic*) override;
};

