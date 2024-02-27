#pragma once
#include "Command.h"
class CLClick_Mouse :
	public CCommand
{
public:
	CLClick_Mouse();
	virtual ~CLClick_Mouse();
public:
	void Initialize() override;
	void Execute() override { LClick(); };
private:
	void LClick();
	void Release() override;
};

