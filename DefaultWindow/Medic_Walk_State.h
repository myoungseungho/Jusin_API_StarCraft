#pragma once
#include "WalkState.h"
class CMedic_Walk_State :
    public IWalkState
{
public:
	CMedic_Walk_State();
	virtual ~CMedic_Walk_State();
public:
	void Initialize(CObj_Dynamic*) override;
	int Update(CObj_Dynamic*) override;
	void Late_Update(CObj_Dynamic*) override;
	void Render(CObj_Dynamic*, HDC hDC) override;
	void Release(CObj_Dynamic*) override;
	void Move_Frame(CObj_Dynamic*) override;
};

