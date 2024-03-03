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
		if (m_Stat.m_Hp <= 0 && !m_OnceDead)
		{
			m_Stat.m_Hp = 0;
			m_OnceDead = true;
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
	void SetAttackRun(bool _bAttackRun) { m_AttackRun = _bAttackRun; }
	bool GetAttackRun() { return m_AttackRun; }
	
	KEYANDFRAME* GetKeyAndFrame() { return &m_KeyAndFrame; }

	bool CheckEnemy();
	POINT GetMousePT() { return m_MousePT; };
	STATEID GetStateID() { return m_CurrentState; }

	virtual DYNAMIC_OBJID GetType() const PURE;

protected:
	float		m_fDistance;
	bool		m_bDead;
	STATEID		m_CurrentState;
	vector<IState*> m_vecState;
	bool		m_OnceDead;
	POINT		m_MousePT;
	bool		m_AttackRun;
	bool		m_Cliecked;

	KEYANDFRAME m_KeyAndFrame;
};

