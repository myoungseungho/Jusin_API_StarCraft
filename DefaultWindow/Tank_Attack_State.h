#pragma once
#include "AttackState.h"
class CTank_Attack_State :
    public IAttackState
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
protected:
    void Move_Frame(CObj_Dynamic*) override;
    virtual void Attack(CObj_Dynamic*) override;
private:
    int         m_TankPosinSize;
    int         m_TankPosinLaunchSize;
    int         m_BulletSize;
    int         m_Offset_Attack;
};

