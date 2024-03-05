#include "stdafx.h"
#include "Ghost_Walk_State.h"
#include "SoundMgr.h"
CGhost_Walk_State::CGhost_Walk_State()
{
}

CGhost_Walk_State::~CGhost_Walk_State()
{
}

void CGhost_Walk_State::Initialize(CObj_Dynamic* _ghost)
{
	vector<wchar_t*> m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound(DYNAMIC_OBJ_MARINE, SOUND_BASIC);
	// 벡터가 비어있지 않은 경우에만 랜덤 인덱스 생성
	if (!m_UnitSound.empty()) {
		int random = rand() % m_UnitSound.size();

		CSoundMgr::Get_Instance()->PlaySound(m_UnitSound[random], SOUND_FIREBAT_WALK, 1);
	}

	m_pFrameCopy = _ghost->Get_Frame();
	m_pFrameKeyCopy = _ghost->Get_FrameKey();

	*m_pFrameKeyCopy = L"Marine_Walk_Right_90";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 17;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 50;
	m_pFrameCopy->dwTime = GetTickCount();

	IWalkState::Initialize(_ghost);
}

int CGhost_Walk_State::Update(CObj_Dynamic* _ghost)
{
	if (Move(_ghost) == MOVE_OK)
		_ghost->ChangeState(IDLE_STATE);

	return 0;
}

void CGhost_Walk_State::Late_Update(CObj_Dynamic*)
{
}

void CGhost_Walk_State::Render(CObj_Dynamic*, HDC hDC)
{
}

void CGhost_Walk_State::Release(CObj_Dynamic*)
{
}

void CGhost_Walk_State::Move_Frame(CObj_Dynamic*)
{
}
