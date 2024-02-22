#pragma once
#include "State.h"
class CFireBat_Idle_State :
    public IState
{
public:
    CFireBat_Idle_State();
    virtual ~CFireBat_Idle_State();
public:
    void Initialize(CObj_Dynamic*) override;
    int Update(CObj_Dynamic*) override;
    void Late_Update(CObj_Dynamic*) override;
    void Render(CObj_Dynamic*, HDC hDC) override;
    void Release(CObj_Dynamic*) override;

    void Move_Frame() override;
};

