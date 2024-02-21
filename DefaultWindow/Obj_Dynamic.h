#pragma once
#include "Obj.h"
#include "State.h"
#include "Define.h"

class IState;

class CObj_Dynamic : public CObj
{
public:
	CObj_Dynamic();
	virtual ~CObj_Dynamic();

public:
	virtual void Initialize() PURE;
	virtual int Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release() PURE;

public:
	void		Set_Dead() { m_bDead = true; }
	bool		Get_Dead() { return m_bDead; }
	void		Move_Frame();
    void		ChangeState(IState*);
protected:
	float		m_fSpeed;
	float		m_fDistance;
	bool		m_bDead;
	IState* m_CurrentState;
};

