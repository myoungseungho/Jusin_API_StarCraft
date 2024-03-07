#include "stdafx.h"
#include "Medic_Die_State.h"
#include "SoundMgr.h"
CMedic_Die_State::CMedic_Die_State()
{
}

CMedic_Die_State::~CMedic_Die_State()
{
}

void CMedic_Die_State::Initialize(CObj_Dynamic* _medic)
{
	vector<wchar_t*> m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound(DYNAMIC_OBJ_MEDIC, SOUND_DIE);
	CSoundMgr::Get_Instance()->PlaySound(m_UnitSound.back(), SOUND_MEDIC_DIE, 1);

	m_pFrameCopy = _medic->Get_Frame();
	m_pFrameKeyCopy = _medic->Get_FrameKey();

	*m_pFrameKeyCopy = L"Medic_Die";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 8;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 150;
	m_pFrameCopy->dwTime = GetTickCount();
}

int CMedic_Die_State::Update(CObj_Dynamic* _medic)
{
	m_pFrameCopy = _medic->Get_Frame();

	if (m_pFrameCopy->iFrameStart == m_pFrameCopy->iFrameEnd)
		_medic->Set_Dead();

	return 0;
}

void CMedic_Die_State::Late_Update(CObj_Dynamic*)
{
}

void CMedic_Die_State::Render(CObj_Dynamic*, HDC hDC)
{
}

void CMedic_Die_State::Release(CObj_Dynamic*)
{
}

void CMedic_Die_State::Move_Frame(CObj_Dynamic*)
{
}
