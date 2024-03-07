#include "stdafx.h"
#include "FireBat_Die_State.h"
#include "SoundMgr.h"
CFireBat_Die_State::CFireBat_Die_State()
{
}

CFireBat_Die_State::~CFireBat_Die_State()
{
}

void CFireBat_Die_State::Initialize(CObj_Dynamic* _fireBat)
{
	vector<wchar_t*> m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound(DYNAMIC_OBJ_FIREBAT, SOUND_DIE);
	CSoundMgr::Get_Instance()->PlaySound(m_UnitSound.back(), SOUND_FIREBAT_DIE, 1);

	m_pFrameCopy = _fireBat->Get_Frame();
	m_pFrameKeyCopy = _fireBat->Get_FrameKey();

	*m_pFrameKeyCopy = L"FireBat_Die";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 9;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 130;
	m_pFrameCopy->dwTime = GetTickCount();
}

int CFireBat_Die_State::Update(CObj_Dynamic* _fireBat)
{
	m_pFrameCopy = _fireBat->Get_Frame();
	if (m_pFrameCopy->iFrameStart == m_pFrameCopy->iFrameEnd)
		_fireBat->Set_Dead();
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
