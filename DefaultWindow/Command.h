#pragma once
#include "Define.h"
class CCommand
{
public:
	CCommand();
	virtual ~CCommand();
public:
	virtual void Initialize() PURE;
	virtual void Initialize(POINT);

	virtual void Execute() PURE;
	virtual void Render(HDC);
};

