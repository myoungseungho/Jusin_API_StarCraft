#pragma once
#include "State.h"
class CFireBat_Walk_State :
    public IState
{
public:
    CFireBat_Walk_State();
    virtual ~CFireBat_Walk_State();
public:
    void Initialize(CObj_Dynamic*) override;
    int Update(CObj_Dynamic*) override;
    void Late_Update(CObj_Dynamic*) override;
    void Render(CObj_Dynamic*, HDC hDC) override;
    void Release(CObj_Dynamic*) override;

    // IState을(를) 통해 상속됨
    void Move_Frame() override;
};

