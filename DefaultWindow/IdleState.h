#pragma once
#include "State.h"
#include "Obj_UI.h"
class IIdleState :
    public IState
{
public:
    IIdleState();
    virtual ~IIdleState();

public:
	void Initialize(CObj_Dynamic*) override;
	int Update(CObj_Dynamic*) override;
	void Late_Update(CObj_Dynamic*) override;
	void Render(CObj_Dynamic*, HDC hDC) override;
	void Release(CObj_Dynamic*) override;
	void Move_Frame(CObj_Dynamic*) override;
protected:
	vector<CObj_UI*> m_vecIcon;
};

