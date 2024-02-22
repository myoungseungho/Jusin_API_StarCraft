#pragma once
#include "State.h"
class CTank_Die_State :
    public IState
{
public:
    CTank_Die_State();
    virtual ~CTank_Die_State();
public:
    void Initialize(CObj_Dynamic*) override;
    int Update(CObj_Dynamic*) override;
    void Late_Update(CObj_Dynamic*) override;
    void Render(CObj_Dynamic*, HDC hDC) override;
    void Release(CObj_Dynamic*) override;
};
