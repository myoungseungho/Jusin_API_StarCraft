#include "stdafx.h"
#include "WalkState.h"
#include "AStarMgr.h"

IWalkState::IWalkState()
{
}

IWalkState::~IWalkState()
{
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
