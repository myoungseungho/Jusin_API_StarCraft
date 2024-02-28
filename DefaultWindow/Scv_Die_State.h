#pragma once
#include "DieState.h"
class CScv_Die_State :
    public IDieState
{
public:
    CScv_Die_State();
    virtual ~CScv_Die_State();
public:
    void Initialize(CObj_Dynamic*) override;
    int Update(CObj_Dynamic*) override;
    void Late_Update(CObj_Dynamic*) override;
    void Render(CObj_Dynamic*, HDC hDC) override;
    void Release(CObj_Dynamic*) override;
    void Move_Frame(CObj_Dynamic*) override;
};

