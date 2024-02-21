#pragma once
#include "Obj_Dynamic.h"
#include "State.h"
class CFireBat : public CObj_Dynamic
{
public:
	CFireBat();
	virtual ~CFireBat();
	CFireBat(const CFireBat&);
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
	CObj* Clone(float _fX, float _fY) override
	{
		CObj* protoType = new CFireBat(*this);
		protoType->Initialize();
		protoType->Set_Pos(_fX, _fY);
		return new CFireBat(*this);
	}

public:
	void ChangeState(IState*);

protected:
	virtual void InsertBmpFile() override;
private:
	IState* m_CurrentState;
};

