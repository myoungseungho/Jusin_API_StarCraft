#include "stdafx.h"
#include "CollectionState.h"
#include "AStarMgr.h"
ICollectionState::ICollectionState()
{
}

ICollectionState::~ICollectionState()
{
}

void ICollectionState::Initialize(CObj_Dynamic*)
{
}

int ICollectionState::Update(CObj_Dynamic*)
{
    return 0;
}

void ICollectionState::Late_Update(CObj_Dynamic*)
{
}

void ICollectionState::Render(CObj_Dynamic*, HDC hDC)
{
}

void ICollectionState::Release(CObj_Dynamic*)
{
}

void ICollectionState::Move_Frame(CObj_Dynamic*)
{
}

void ICollectionState::Set_Astar(float _fX, float _fY, float _goalX, float _goalY)
{
	pair<int, int> start(_fX, _fY);
	pair<int, int> goal(_goalX, _goalY);

	m_Path = CAStarMgr::Get_Instance()->SCV_AStarSearch(start, goal);
}
