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

void ICollectionState::Move_Frame(CObj_Dynamic* _scv)
{
	if (m_tFrame_Attack.dwTime + m_tFrame_Attack.dwSpeed < GetTickCount())
	{
		++m_tFrame_Attack.iFrameStart;

		if (m_tFrame_Attack.iFrameStart > m_tFrame_Attack.iFrameEnd)
			m_tFrame_Attack.iFrameStart = 0;

		m_tFrame_Attack.dwTime = GetTickCount();
	}
}

void ICollectionState::Set_Astar(float _fX, float _fY, float _goalX, float _goalY)
{
	pair<int, int> start(_fX, _fY);
	pair<int, int> goal(_goalX, _goalY);

	m_Path = CAStarMgr::Get_Instance()->SCV_AStarSearch(start, goal);
}
