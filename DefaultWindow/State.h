#pragma once
#include "Define.h"
#include "Obj_Dynamic.h"

class CObj;
class CObj_Dynamic;
class IState
{
public:
	IState();
	virtual ~IState();

public:
	virtual void		Initialize(CObj_Dynamic*)	PURE;
	virtual int			Update(CObj_Dynamic*)		PURE;
	virtual void		Late_Update(CObj_Dynamic*)	PURE;
	virtual void		Render(CObj_Dynamic*, HDC hDC)	PURE;
	virtual void		Release(CObj_Dynamic*)		PURE;
protected:
	virtual void Move_Frame(CObj_Dynamic*) PURE;
public:
	virtual void Set_Astar(float, float, float, float);
	int Move(CObj_Dynamic* _unit);
protected:
	list<CObj*> m_listPathTile;
	list<pair<int, int>> m_Path;
	DWORD m_dwTime;

	//∏ﬁ¿Œ
	FRAME* m_pFrameCopy;
	TCHAR** m_pFrameKeyCopy;

	//≈ ≈© ∆˜Ω≈
	FRAME  m_tFrame_TankPosin;
	TCHAR* m_pFrameKey_TankPosin;

	//««∞›
	FRAME  m_tFrame_Attack;
	TCHAR* m_pFrameKey_Attack;
		
	//≈ ≈© ∆˜Ω≈¿Ã∆Â∆Æ
	FRAME  m_tFrame_Attack_TankPosin;
	TCHAR* m_pFrameKey_Attack_TankPosin;

	//Ω√¡Ó≈ ≈© On
	FRAME  m_tFrame_SiegeOn;
	TCHAR* m_pFrameKey_SiegeOn;

	//Ω√¡Ó≈ ≈© off
	FRAME  m_tFrame_SiegeOff;
	TCHAR* m_pFrameKey_SiegeOff;

	//Ω√¡Ó≈ ≈©
	FRAME  m_tFrame_Attack_Siege;
	TCHAR* m_pFrameKey_Attack_Siege;
protected:
	void DetermineKey(CObj_Dynamic*, float);
private:
	bool m_bSiegeAttack;
};

