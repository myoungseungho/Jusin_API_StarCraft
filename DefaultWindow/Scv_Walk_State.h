#pragma once
#include "WalkState.h"
class CScv_Walk_State :
    public IWalkState
{
public:
    CScv_Walk_State();
    virtual ~CScv_Walk_State();
public:
    void Initialize(CObj_Dynamic*) override;
    int Update(CObj_Dynamic*) override;
    void Late_Update(CObj_Dynamic*) override;
    void Render(CObj_Dynamic*, HDC hDC) override;
    void Release(CObj_Dynamic*) override;

    // IState을(를) 통해 상속됨
    void Move_Frame() override;
};

