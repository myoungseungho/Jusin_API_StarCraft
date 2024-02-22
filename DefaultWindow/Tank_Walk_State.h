#pragma once
#include "State.h"
class CTank_Walk_State :
    public IState
{
public:
	CTank_Walk_State();
	virtual ~CTank_Walk_State();
public:
	void Initialize(CObj_Dynamic*) override;
	int Update(CObj_Dynamic*) override;
	void Late_Update(CObj_Dynamic*) override;
	void Render(CObj_Dynamic*, HDC hDC) override;
	void Release(CObj_Dynamic*) override;

	// IState을(를) 통해 상속됨
	void Move_Frame() override;
};

