#pragma once
#include "Define.h"
#include "Obj_Dynamic.h"
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
	virtual void		Render(CObj_Dynamic* ,HDC hDC)	PURE;
	virtual void		Release(CObj_Dynamic*)		PURE;
protected:
	virtual void Move_Frame() PURE;
protected:
	FRAME* m_pFrameCopy;
	TCHAR** m_pFrameKeyCopy;
};

