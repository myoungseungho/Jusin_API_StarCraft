#pragma once
#include "Define.h"
#include "Obj.h"
class IState
{
public:
	IState();
	virtual ~IState();

public:
	virtual void		Initialize(CObj*)	PURE;
	virtual int			Update(CObj*)		PURE;
	virtual void		Late_Update(CObj*)	PURE;
	virtual void		Render(CObj* ,HDC hDC)	PURE;
	virtual void		Release(CObj*)		PURE;
protected:
	FRAME* m_pFrameCopy;
	TCHAR** m_pFrameKeyCopy;
};

