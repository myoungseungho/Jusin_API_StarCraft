#pragma once
#include "State.h"
class CFireBat_Attack_State :
    public IState
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
    
private:
    TCHAR*      m_pFrameKey_Attack;
    FRAME		m_tFrame_Attack;

    // IState을(를) 통해 상속됨
    void Move_Frame() override;
};

