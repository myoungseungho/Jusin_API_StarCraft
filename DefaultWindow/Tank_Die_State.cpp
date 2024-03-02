#include "stdafx.h"
#include "Tank_Die_State.h"
#include "SoundMgr.h"
CTank_Die_State::CTank_Die_State()
{
}

CTank_Die_State::~CTank_Die_State()
{
}

void CTank_Die_State::Initialize(CObj_Dynamic* _tank)
{
	vector<wchar_t*> m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound(DYNAMIC_OBJ_TANK, SOUND_DIE);
	CSoundMgr::Get_Instance()->PlaySound(m_UnitSound.back(), SOUND_TANK_DIE, 1);

	m_pFrameCopy = _tank->Get_Frame();
	m_pFrameKeyCopy = _tank->Get_FrameKey();

	*m_pFrameKeyCopy = L"Tank_BANG";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 13;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 50;
	m_pFrameCopy->dwTime = GetTickCount();
}

int CTank_Die_State::Update(CObj_Dynamic* _tank)
{
	m_pFrameCopy = _tank->Get_Frame();

	if (m_pFrameCopy->iFrameStart == m_pFrameCopy->iFrameEnd)
		_tank->Set_Dead();

	return 0;
}

void CTank_Die_State::Late_Update(CObj_Dynamic*)
{
}

void CTank_Die_State::Render(CObj_Dynamic*, HDC hDC)
{
}

void CTank_Die_State::Release(CObj_Dynamic*)
{
}

void CTank_Die_State::Move_Frame(CObj_Dynamic*)
{
}
