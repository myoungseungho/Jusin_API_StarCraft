#pragma once
#include "State.h"
class CIdle_State :
    public CState
{
public:
    CIdle_State();
    virtual ~CIdle_State();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};



