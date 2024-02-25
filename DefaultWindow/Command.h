#pragma once
#include "Define.h"
class CCommand
{
public:
	CCommand();
	virtual ~CCommand();
public:
	virtual void Execute() PURE;
};

