#pragma once
#include "State.h"
class CTank_Attack_State :
    public IState
{
public:
    CTank_Attack_State();
    virtual ~CTank_Attack_State();
public:
    void Initialize(CObj_Dynamic*) override;
    int Update(CObj_Dynamic*) override;
    void Late_Update(CObj_Dynamic*) override;
    void Render(CObj_Dynamic*, HDC hDC) override;
    void Release(CObj_Dynamic*) override;

    // IState��(��) ���� ��ӵ�
    void Move_Frame() override;
};

