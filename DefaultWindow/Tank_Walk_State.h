#pragma once
#include "WalkState.h"
class CTank_Walk_State :
    public IWalkState
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
	void Move_Frame(CObj_Dynamic*) override;
private:
	int m_AttackFileSize = 128;
	int m_Offset_Attack = 0;
};

