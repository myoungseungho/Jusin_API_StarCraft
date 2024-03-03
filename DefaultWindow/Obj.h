#pragma once
#include "Define.h"
class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}

	void		Set_PosX(float _fX) { m_tInfo.fX += _fX; }
	void		Set_PosY(float _fY) { m_tInfo.fY += _fY; }

	void		Set_Dir(DIRECTION eDir) { m_eDir = eDir; }
	virtual void		Set_Dead()
	{
		m_bDead = true;
	}
	bool		Get_Dead() { return m_bDead; }

	RECT		Get_Rect() { return m_tRect; }
	void		Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void		Set_Target(CObj* pTarget) { m_pTarget = pTarget; }
	void		Set_Clear_Target() { m_pTarget = nullptr; }
	void		Set_CollisionState(COLLISIONSTATE _cId) { m_Collision = _cId; };
	CObj* Get_Target() { return m_pTarget; }
	COLLISIONSTATE Get_CollisionState() { return m_Collision; };


	INFO		Get_Info() { return m_tInfo; }
	RENDERID	Get_RenderID() { return m_eRender; }

public:
	virtual void		Initialize()	PURE;
	virtual int			Update()		PURE;
	virtual void		Late_Update()	PURE;
	virtual void		Render(HDC hDC)	PURE;
	virtual void		Release()		PURE;
public:
	void		Update_Rect();

	FRAME* Get_Frame() { return &m_tFrame; }
	TCHAR** Get_FrameKey() { return &m_pFrameKey; }
	FACTIONSTATE Get_FactionState() { return m_Faction; }
	void		Set_FactionState(FACTIONSTATE m_Id) { m_Faction = m_Id; };
	void		Set_FrameKey(TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }
	STAT		Get_Stat() { return m_Stat; };
	void		Set_Cliecked(bool _bClick) { m_bCliecked = _bClick; };
protected:
	virtual void InsertBmpFile();

protected:
	INFO		m_tInfo;
	RECT		m_tRect;

	DIRECTION	m_eDir;
	float		m_fAngle;

	CObj* m_pTarget;

	TCHAR* m_pFrameKey;
	FRAME		m_tFrame;

	RENDERID	m_eRender;

	FACTIONSTATE m_Faction;

	bool m_bDead;

	COLLISIONSTATE m_Collision;

	STAT m_Stat;
	bool		m_bCliecked;
};

