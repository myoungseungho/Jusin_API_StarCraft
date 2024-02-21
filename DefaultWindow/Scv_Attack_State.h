#pragma once
#include "State.h"
class CScv_Attack_State :
    public IState
{
public:
    CScv_Attack_State();
    virtual ~CScv_Attack_State();
public:
    void Initialize(CObj*) override;
    int Update(CObj*) override;
    void Late_Update(CObj*) override;
    void Render(CObj*, HDC hDC) override;
    void Release(CObj*) override;
};

