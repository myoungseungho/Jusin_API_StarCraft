#pragma once
#include "AttackState.h"
class CTank_Siege_Mode :
    public IAttackState
{
public:
	CTank_Siege_Mode();
	virtual ~CTank_Siege_Mode();
public:
	void Initialize(CObj_Dynamic*) override;
	int Update(CObj_Dynamic*) override;
	void Late_Update(CObj_Dynamic*) override;
	void Render(CObj_Dynamic*, HDC hDC) override;
	void Release(CObj_Dynamic*) override;
	void Move_Frame(CObj_Dynamic*) override;
public:
	void SetDefaultMode();
private:
	bool m_bIdleReady;
};

