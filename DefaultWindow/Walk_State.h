#pragma once
#include "State.h"
class CWalk_State :
    public CState
{
public:
    CWalk_State();
    virtual ~CWalk_State();
public:
    void Initialize() PURE;
    int Update() PURE;
    void Late_Update() PURE;
    void Render(HDC hDC) PURE;
    void Release() PURE;
};

