#pragma once
#include "IdleState.h"
class CMarine_Idle_State :
    public IIdleState
{
public:
    CMarine_Idle_State();
    virtual ~CMarine_Idle_State();
public:
    void Initialize(CObj_Dynamic*) override;
    int Update(CObj_Dynamic*) override;
    void Late_Update(CObj_Dynamic*) override;
    void Render(CObj_Dynamic*, HDC hDC) override;
    void Release(CObj_Dynamic*) override;

    // IState을(를) 통해 상속됨
    void Move_Frame() override;
};

