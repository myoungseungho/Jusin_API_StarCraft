#include "stdafx.h"
#include "FireBat.h"

CFireBat::CFireBat() : m_CurrentState(nullptr)
{
	InsertBmpFile();
}

CFireBat::~CFireBat()
{
}

CFireBat::CFireBat(const CFireBat&) : m_CurrentState(nullptr)
{
}

void CFireBat::Initialize()
{
}

int CFireBat::Update()
{
	return 0;
}

void CFireBat::Late_Update()
{
}

void CFireBat::Render(HDC hDC)
{
}

void CFireBat::Release()
{

}

void CFireBat::ChangeState(IState*)
{
}

void CFireBat::InsertBmpFile()
{
}
