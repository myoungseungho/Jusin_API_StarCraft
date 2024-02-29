#pragma once
#include "AttackState.h"
class CFireBat_Attack_State :
    public IAttackState
{
public:
    CFireBat_Attack_State();
    virtual ~CFireBat_Attack_State();
public:
    void Initialize(CObj_Dynamic*) override;
    int Update(CObj_Dynamic*) override;
    void Late_Update(CObj_Dynamic*) override;
    void Render(CObj_Dynamic*, HDC hDC) override;
    void Release(CObj_Dynamic*) override;
    
protected:
    virtual void Move_Frame(CObj_Dynamic*) override;
    virtual void Attack(CObj_Dynamic*) override;

private:
    TCHAR*      m_pFrameKey_Attack;
    FRAME		m_tFrame_Attack;
    int         m_AttackFileSize;
    int         m_Offset_Attack;
};

