#include "stdafx.h"
#include "Medic_Walk_State.h"
#include "TileMgr.h"
#include "SoundMgr.h"
CMedic_Walk_State::CMedic_Walk_State()
{
}

CMedic_Walk_State::~CMedic_Walk_State()
{
}

void CMedic_Walk_State::Initialize(CObj_Dynamic* _medic)
{
	vector<wchar_t*> m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound(DYNAMIC_OBJ_MEDIC, SOUND_BASIC);
	// 벡터가 비어있지 않은 경우에만 랜덤 인덱스 생성
	if (!m_UnitSound.empty()) {
		int random = rand() % m_UnitSound.size();

		CSoundMgr::Get_Instance()->PlaySound(m_UnitSound[random], SOUND_MEDIC_WALK, 1);
	}

	m_pFrameCopy = _medic->Get_Frame();
	m_pFrameKeyCopy = _medic->Get_FrameKey();

	*m_pFrameKeyCopy = L"Medic_Walk_Right_90";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 13;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 50;
	m_pFrameCopy->dwTime = GetTickCount();
	
	IWalkState::Initialize(_medic);
}

int CMedic_Walk_State::Update(CObj_Dynamic* _medic)
{
	if (Move(_medic) == MOVE_OK)
		_medic->ChangeState(IDLE_STATE);
	else
	{
		_medic->CheckEnemy();
	}
	return 0;
}

void CMedic_Walk_State::Late_Update(CObj_Dynamic*)
{
}

void CMedic_Walk_State::Render(CObj_Dynamic*, HDC hDC)
{
}

void CMedic_Walk_State::Release(CObj_Dynamic*)
{
}

void CMedic_Walk_State::Move_Frame(CObj_Dynamic*)
{
}

