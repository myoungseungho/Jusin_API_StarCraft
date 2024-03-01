#pragma once
#include "IdleState.h"
class CTank_Idle_State :
    public IIdleState
{
public:
	CTank_Idle_State();
	virtual ~CTank_Idle_State();
public:
	void Initialize(CObj_Dynamic*) override;
	int Update(CObj_Dynamic*) override;
	void Late_Update(CObj_Dynamic*) override;
	void Render(CObj_Dynamic*, HDC hDC) override;
	void Release(CObj_Dynamic*) override;
	void Move_Frame(CObj_Dynamic*) override;

private:
	int         m_AttackFileSize;
	int         m_Offset_Attack;
};

