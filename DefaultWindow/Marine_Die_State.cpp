#include "stdafx.h"
#include "Marine_Die_State.h"
#include "SoundMgr.h"
CMarine_Die_State::CMarine_Die_State()
{
}

CMarine_Die_State::~CMarine_Die_State()
{
}

void CMarine_Die_State::Initialize(CObj_Dynamic* _marine)
{
	vector<wchar_t*> m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound(DYNAMIC_OBJ_MARINE, SOUND_DIE);
	CSoundMgr::Get_Instance()->PlaySound(m_UnitSound.back(), SOUND_MARINE_DIE, 1);

	m_pFrameCopy = _marine->Get_Frame();
	m_pFrameKeyCopy = _marine->Get_FrameKey();

	*m_pFrameKeyCopy = L"Marine_Dead";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 7;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 50;
	m_pFrameCopy->dwTime = GetTickCount();
}

int CMarine_Die_State::Update(CObj_Dynamic* _marine)
{
	m_pFrameCopy = _marine->Get_Frame();

	if (m_pFrameCopy->iFrameStart == m_pFrameCopy->iFrameEnd)
		_marine->Set_Dead();

	return 0;
}

void CMarine_Die_State::Late_Update(CObj_Dynamic* _marine)
{
}

void CMarine_Die_State::Render(CObj_Dynamic*, HDC hDC)
{
}

void CMarine_Die_State::Release(CObj_Dynamic*)
{
}

void CMarine_Die_State::Move_Frame(CObj_Dynamic* _unit)
{

}
