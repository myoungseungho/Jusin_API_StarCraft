#include "stdafx.h"
#include "FireBat_Die_State.h"

CFireBat_Die_State::CFireBat_Die_State()
{
}

CFireBat_Die_State::~CFireBat_Die_State()
{
}

void CFireBat_Die_State::Initialize(CObj_Dynamic*)
{
}

int CFireBat_Die_State::Update(CObj_Dynamic* _fireBat)
{
	if (_fireBat->Get_Frame()->iFrameStart  == _fireBat->Get_Frame()->iFrameEnd)
	{
		_fireBat->Set_Dead();
	}

	return 0;
}

void CFireBat_Die_State::Late_Update(CObj_Dynamic*)
{
}

void CFireBat_Die_State::Render(CObj_Dynamic*, HDC hDC)
{
}

void CFireBat_Die_State::Release(CObj_Dynamic*)
{
}

void CFireBat_Die_State::Move_Frame(CObj_Dynamic*)
{
}
