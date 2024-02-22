#pragma once
#include "State.h"
class CScv_Idle_State :
	public IState
{
public:
	CScv_Idle_State();
	virtual ~CScv_Idle_State();
public:
	void Initialize(CObj_Dynamic*) override;
	int Update(CObj_Dynamic*) override;
	void Late_Update(CObj_Dynamic*) override;
	void Render(CObj_Dynamic* ,HDC hDC) override;
	void Release(CObj_Dynamic*) override;

	// IState��(��) ���� ��ӵ�
	void Move_Frame() override;
};

