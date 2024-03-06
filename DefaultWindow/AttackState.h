#pragma once
#include "State.h"
class IAttackState :
    public IState
{
public:
	IAttackState();
	virtual ~IAttackState();

public:
	void Initialize(CObj_Dynamic*) override;
	int Update(CObj_Dynamic*) override;
	void Late_Update(CObj_Dynamic*) override;
	void Render(CObj_Dynamic*, HDC hDC) override;
	void Release(CObj_Dynamic*) override;
	void Move_Frame(CObj_Dynamic*) override;
	virtual void Attack(CObj_Dynamic*);

protected:
	virtual void MoveUntilAttackDistance(CObj_Dynamic*);

private:
	float m_currentTime;
};

