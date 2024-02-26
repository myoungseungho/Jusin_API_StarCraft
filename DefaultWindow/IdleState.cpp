#include "stdafx.h"
#include "IdleState.h"

IIdleState::IIdleState()
{
}

IIdleState::~IIdleState()
{
}

void IIdleState::Initialize(CObj_Dynamic*)
{
}

int IIdleState::Update(CObj_Dynamic*)
{
	return 0;
}

void IIdleState::Late_Update(CObj_Dynamic*)
{
}

void IIdleState::Render(CObj_Dynamic*, HDC hDC)
{
}

void IIdleState::Release(CObj_Dynamic*)
{
}

void IIdleState::Move_Frame()
{
}
