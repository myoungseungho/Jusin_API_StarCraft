#pragma once
#include "State.h"
class CWalk_State :
    public CState
{
public:
    CWalk_State();
    virtual ~CWalk_State();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

