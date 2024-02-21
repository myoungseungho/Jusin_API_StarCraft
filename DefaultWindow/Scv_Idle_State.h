#pragma once
#include "State.h"
class CScv_Idle_State :
	public IState
{
public:
	CScv_Idle_State();
	virtual ~CScv_Idle_State();
public:
	void Initialize(CObj*) override;
	int Update(CObj*) override;
	void Late_Update(CObj*) override;
	void Render(CObj* ,HDC hDC) override;
	void Release(CObj*) override;
};

