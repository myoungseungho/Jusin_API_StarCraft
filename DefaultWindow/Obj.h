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

	RECT		Get_Rect() { return m_tRect; }
	void		Set_Dead() { m_bDead = true; }
	void		Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void		Set_Target(CObj* pTarget) { m_pTarget = pTarget; }
	bool		Get_Dead() { return m_bDead; }
	void		Set_FrameKey(TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }
	FRAME*		Get_Frame() { return &m_tFrame; }
	TCHAR*		Get_FrameKey() { return m_pFrameKey; }
	INFO		Get_Info() { return m_tInfo; }
	RENDERID	Get_RenderID() { return m_eRender; }

public:
	virtual void		Initialize()	PURE;
	virtual int			Update()		PURE;
	virtual void		Late_Update()	PURE;
	virtual void		Render(HDC hDC)	PURE;
	virtual void		Release()		PURE;
	virtual CObj* Clone(float, float);
public:
	void		Update_Rect();
	void		Move_Frame();

protected:
	virtual void InsertBmpFile();

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	FRAME		m_tFrame;

	float		m_fSpeed;
	float		m_fAngle;
	float		m_fDistance;

	DIRECTION	m_eDir;
	bool		m_bDead;

	CObj* m_pTarget;
	TCHAR* m_pFrameKey;

	RENDERID	m_eRender;
};

