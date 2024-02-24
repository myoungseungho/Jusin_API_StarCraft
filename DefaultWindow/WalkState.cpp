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

	m_Path = CAStarMgr::Get_Instance()->AStarSearch(start, goal);
}

void IWalkState::Initialize(CObj_Dynamic*)
{
}

int IWalkState::Update(CObj_Dynamic* _unit)
{
	return 0;
}

void IWalkState::Late_Update(CObj_Dynamic*)
{
}

void IWalkState::Render(CObj_Dynamic*, HDC hDC)
{
}

void IWalkState::Release(CObj_Dynamic*)
{
}

void IWalkState::Move_Frame()
{
}
