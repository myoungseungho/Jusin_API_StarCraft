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
	virtual void Release();

public:
	void		Set_Dead() { m_bDead = true; }
	bool		Get_Dead() { return m_bDead; }
	void		Set_Damage(float m_attack)
	{
		m_Stat.m_Hp -= m_attack;
		if (m_Stat.m_Hp <= 0)
		{
			m_Stat.m_Hp = 0;

			CObj_Dynamic* dynamic_obj = dynamic_cast<CObj_Dynamic*>(this);
			if (dynamic_cast<CObj_Dynamic*>(this))
			{
				dynamic_obj->ChangeState(DIE_STATE);
			}
		}
	};
	void		Move_Frame();

	void		ChangeState(STATEID);

	void ChangeStateWithMouse(POINT _pt, STATEID _sId);
	bool CheckEnemy();
	POINT GetMousePT() { return m_MousePT; };

	virtual DYNAMIC_OBJID GetType() const PURE;

protected:
	float		m_fDistance;
	bool		m_bDead;
	STATEID		m_CurrentState;
	vector<IState*> m_vecState;

	POINT		m_MousePT;
};

