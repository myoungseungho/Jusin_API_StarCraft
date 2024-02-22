#pragma once
#include "State.h"
class CMedic_Idle_State :
    public IState
{
public:
	CMedic_Idle_State();
	virtual ~CMedic_Idle_State();
public:
	void Initialize(CObj_Dynamic*) override;
	int Update(CObj_Dynamic*) override;
	void Late_Update(CObj_Dynamic*) override;
	void Render(CObj_Dynamic*, HDC hDC) override;
	void Release(CObj_Dynamic*) override;

	// IState을(를) 통해 상속됨
	void Move_Frame() override;
};

