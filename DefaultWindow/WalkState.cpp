#include "stdafx.h"
#include "WalkState.h"
#include "AStarMgr.h"

IWalkState::IWalkState()
{
}

IWalkState::~IWalkState()
{
}

void IWalkState::Set_Astar(float _fX, float _fY, float _goalX, float _goalY)
{
	pair<int, int> start(_fX, _fY);
	pair<int, int> goal(_goalX, _goalY);

	vector<pair<int,int>> path = CAStarMgr::Get_Instance()->AStarSearch(start, goal);
	int i = 3;
}
