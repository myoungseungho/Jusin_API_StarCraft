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
	void		Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void		Set_Target(CObj* pTarget) { m_pTarget = pTarget; }
	
	INFO		Get_Info() { return m_tInfo; }
	RENDERID	Get_RenderID() { return m_eRender; }

public:
	virtual void		Initialize()	PURE;
	virtual int			Update()		PURE;
	virtual void		Late_Update()	PURE;
	virtual void		Render(HDC hDC)	PURE;
	virtual void		Release()		PURE;
	virtual CObj*		Clone(float, float);
public:
	void		Update_Rect();

	FRAME*		Get_Frame() { return &m_tFrame; }
	TCHAR**		Get_FrameKey() { return &m_pFrameKey; }
	void		Set_FrameKey(TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }
protected:
	virtual void InsertBmpFile();

protected:
	INFO		m_tInfo;
	RECT		m_tRect;

	DIRECTION	m_eDir;
	float		m_fAngle;

	CObj* m_pTarget;

	TCHAR*		m_pFrameKey;
	FRAME		m_tFrame;

	RENDERID	m_eRender;
};

