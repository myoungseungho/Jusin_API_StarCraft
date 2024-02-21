#pragma once
#include "State.h"
class CAttack_State :
    public CState
{
public:
    CAttack_State();
    virtual ~CAttack_State();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

