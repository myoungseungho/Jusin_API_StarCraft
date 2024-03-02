#include "stdafx.h"
#include "FireBat_Walk_State.h"
#include "TileMgr.h"
#include "SoundMgr.h"
CFireBat_Walk_State::CFireBat_Walk_State()
{
}

CFireBat_Walk_State::~CFireBat_Walk_State()
{
}

void CFireBat_Walk_State::Initialize(CObj_Dynamic* _fireBat)
{
	vector<wchar_t*> m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound(DYNAMIC_OBJ_FIREBAT, SOUND_BASIC);
	// 벡터가 비어있지 않은 경우에만 랜덤 인덱스 생성
	if (!m_UnitSound.empty()) {
		int random = rand() % m_UnitSound.size();

		CSoundMgr::Get_Instance()->PlaySound(m_UnitSound[random], SOUND_FIREBAT_WALK, 1);
	}
	m_pFrameCopy = _fireBat->Get_Frame();
	m_pFrameKeyCopy = _fireBat->Get_FrameKey();

	*m_pFrameKeyCopy = L"Firebat_Work_Up_Right_90";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 15;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 50;
	m_pFrameCopy->dwTime = GetTickCount();

	IWalkState::Initialize(_fireBat);
}

int CFireBat_Walk_State::Update(CObj_Dynamic* _fireBat)
{
	if (Move(_fireBat) == MOVE_OK)
		_fireBat->ChangeState(IDLE_STATE);
	else
	{
		_fireBat->CheckEnemy();
	}
	return 0;
}

void CFireBat_Walk_State::Late_Update(CObj_Dynamic*)
{
}

void CFireBat_Walk_State::Render(CObj_Dynamic*, HDC hDC)
{
}

void CFireBat_Walk_State::Release(CObj_Dynamic*)
{
}

void CFireBat_Walk_State::Move_Frame(CObj_Dynamic*)
{
}
