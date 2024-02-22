#pragma once
#include "State.h"
class CMarine_Die_State :
    public IState
{
public:
    CMarine_Die_State();
    virtual ~CMarine_Die_State();
public:
    void Initialize(CObj_Dynamic*) override;
    int Update(CObj_Dynamic*) override;
    void Late_Update(CObj_Dynamic*) override;
    void Render(CObj_Dynamic*, HDC hDC) override;
    void Release(CObj_Dynamic*) override;
};

