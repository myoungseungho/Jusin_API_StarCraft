#include "stdafx.h"
#include "Tank_Walk_State.h"
#include "TileMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SoundMgr.h"
CTank_Walk_State::CTank_Walk_State()
{
}

CTank_Walk_State::~CTank_Walk_State()
{
}

void CTank_Walk_State::Initialize(CObj_Dynamic* _tank)
{
	if (_tank->Get_FactionState() == FACTION_ALLY)
	{
		vector<wchar_t*> m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound(DYNAMIC_OBJ_TANK, SOUND_BASIC);
		// 벡터가 비어있지 않은 경우에만 랜덤 인덱스 생성
		if (!m_UnitSound.empty()) {
			int random = rand() % m_UnitSound.size();

			CSoundMgr::Get_Instance()->PlaySound(m_UnitSound[random], SOUND_TANK_WALK, 1);
		}
	}

	m_pFrameCopy = _tank->Get_Frame();
	m_pFrameKeyCopy = _tank->Get_FrameKey();

	*m_pFrameKeyCopy = L"Lower_Tank_Walk_Right_90";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 5;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 50;
	m_pFrameCopy->dwTime = GetTickCount();

	m_pFrameKey_TankPosin = L"Tank_Upper_Right";
	m_tFrame_TankPosin.iFrameStart = 0;
	m_tFrame_TankPosin.iFrameEnd = 0;
	m_tFrame_TankPosin.iMotion = 0;
	m_tFrame_TankPosin.dwSpeed = 50;
	m_tFrame_TankPosin.dwTime = GetTickCount();

	m_TankPosinSize = 128;

	IWalkState::Initialize(_tank);
}

int CTank_Walk_State::Update(CObj_Dynamic* _tank)
{
	if (Move(_tank) == MOVE_OK)
		_tank->ChangeState(IDLE_STATE);
	else
	{
		_tank->CheckEnemy();
	}

    return 0;
}

void CTank_Walk_State::Late_Update(CObj_Dynamic* _tank)
{
	Move_Frame(_tank);
}

void CTank_Walk_State::Render(CObj_Dynamic* _tank, HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey_TankPosin);

	GdiTransparentBlt(
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		(_tank->Get_Rect().left + iScrollX), // 복사 받을 위치 좌표
		(_tank->Get_Rect().top + iScrollY),
		m_TankPosinSize,	// 복사 받을 이미지의 가로, 세로
		m_TankPosinSize,
		hMemDC,		// 비트맵을 가지고 있는 DC
		m_TankPosinSize * m_tFrame_TankPosin.iFrameStart,			// 비트맵 출력 시작 좌표 LEFT, TOP
		m_TankPosinSize * m_tFrame_TankPosin.iMotion,
		m_TankPosinSize,	// 출력할 비트맵 가로
		m_TankPosinSize,	// 출력할 비트맵 세로
		RGB(0, 0, 0));	// 제거할 색상 값
}

void CTank_Walk_State::Release(CObj_Dynamic*)
{
}

void CTank_Walk_State::Move_Frame(CObj_Dynamic*)
{
	if (m_tFrame_TankPosin.dwTime + m_tFrame_TankPosin.dwSpeed < GetTickCount())
	{
		++m_tFrame_TankPosin.iFrameStart;

		if (m_tFrame_TankPosin.iFrameStart > m_tFrame_TankPosin.iFrameEnd)
		{
			m_tFrame_TankPosin.iFrameStart = 0;
		}

		m_tFrame_TankPosin.dwTime = GetTickCount();
	}
}

