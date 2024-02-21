#pragma once
#include "Define.h"
class CState
{
public:
	CState();
	virtual ~CState();

public:
	virtual void		Initialize()	PURE;
	virtual int			Update()		PURE;
	virtual void		Late_Update()	PURE;
	virtual void		Render(HDC hDC)	PURE;
	virtual void		Release()		PURE;
};

