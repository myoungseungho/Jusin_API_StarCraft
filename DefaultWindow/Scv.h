#pragma once
#include "Obj.h"
#include "State.h"
class CScv : public CObj
{
public:
	CScv();
	CScv(const CScv&);
	virtual ~CScv();
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	CObj* Clone(float _fX, float _fY) override
	{
		CObj* protoType = new CScv(*this);
		protoType->Initialize();
		protoType->Set_Pos(_fX, _fY);
		return new CScv(*this);
	}

public:
	void ChangeState(IState*);

protected:
	virtual void InsertBmpFile() override;
private:
	IState* m_CurrentState;
};

