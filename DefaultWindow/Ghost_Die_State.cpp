#include "stdafx.h"
#include "Ghost_Die_State.h"
#include "SoundMgr.h"

CGhost_Die_State::CGhost_Die_State()
{
}

CGhost_Die_State::~CGhost_Die_State()
{
}

void CGhost_Die_State::Initialize(CObj_Dynamic* _ghost)
{
	vector<wchar_t*> m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound(DYNAMIC_OBJ_MEDIC, SOUND_DIE);
	CSoundMgr::Get_Instance()->PlaySound(m_UnitSound.back(), SOUND_MEDIC_DIE, 1);

	m_pFrameCopy = _ghost->Get_Frame();
	m_pFrameKeyCopy = _ghost->Get_FrameKey();

	*m_pFrameKeyCopy = L"Ghost_Die";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 8;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 100;
	m_pFrameCopy->dwTime = GetTickCount();
}

int CGhost_Die_State::Update(CObj_Dynamic* _ghost)
{
	m_pFrameCopy = _ghost->Get_Frame();

	if (m_pFrameCopy->iFrameStart == m_pFrameCopy->iFrameEnd)
		_ghost->Set_Dead();
	return 0;
}

void CGhost_Die_State::Late_Update(CObj_Dynamic*)
{
}

void CGhost_Die_State::Render(CObj_Dynamic*, HDC hDC)
{
}

void CGhost_Die_State::Release(CObj_Dynamic*)
{
}

void CGhost_Die_State::Move_Frame(CObj_Dynamic*)
{
}
