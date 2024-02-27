#pragma once
#include "Command.h"
#include "Define.h"
#include "Obj.h"
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
	void HandleUIClick(POINT);
	void HandleDynamicObjectClick(CObj*);
	void HandleStaticObjectClick(CObj*);
	void HandleNoTargetClick();
	void Release() override;
};

