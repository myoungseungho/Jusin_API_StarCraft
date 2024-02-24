#pragma once
#include "State.h"
class IWalkState :
	public IState
{
public:
	IWalkState();
	virtual ~IWalkState();
public:
	void Set_Astar(float, float, float, float);
};

