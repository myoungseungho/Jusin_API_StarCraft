#include "stdafx.h"
#include "AttackState.h"

IAttackState::IAttackState() : m_bAttackDistanceIn(false)
{
}

IAttackState::~IAttackState()
{
}

void IAttackState::Initialize(CObj_Dynamic*)
{
}

int IAttackState::Update(CObj_Dynamic*)
{
    return 0;
}

void IAttackState::Late_Update(CObj_Dynamic*)
{
}

void IAttackState::Render(CObj_Dynamic*, HDC hDC)
{
}

void IAttackState::Release(CObj_Dynamic*)
{
}

void IAttackState::Move_Frame(CObj_Dynamic*)
{
}


void IAttackState::MoveUntilAttackDistance(CObj_Dynamic* _marine)
{
}
