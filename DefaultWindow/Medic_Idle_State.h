#pragma once
#include "IdleState.h"
class CMedic_Idle_State :
    public IIdleState
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

	// IState��(��) ���� ��ӵ�
	void Move_Frame() override;
};

