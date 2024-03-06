#pragma once
#include "AttackState.h"
class CGhost_Attack_State :
    public IAttackState
{
public:
	CGhost_Attack_State();
	virtual ~CGhost_Attack_State();

public:
	void Initialize(CObj_Dynamic*) override;
	int Update(CObj_Dynamic*) override;
	void Late_Update(CObj_Dynamic*) override;
	void Render(CObj_Dynamic*, HDC hDC) override;
	void Release(CObj_Dynamic*) override;
protected:
	virtual void Attack(CObj_Dynamic*) override;
	virtual void MoveUntilAttackDistance(CObj_Dynamic*) override;
};

