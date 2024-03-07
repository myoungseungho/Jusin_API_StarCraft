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
		// ���Ͱ� ������� ���� ��쿡�� ���� �ε��� ����
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
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		(_tank->Get_Rect().left + iScrollX), // ���� ���� ��ġ ��ǥ
		(_tank->Get_Rect().top + iScrollY),
		m_TankPosinSize,	// ���� ���� �̹����� ����, ����
		m_TankPosinSize,
		hMemDC,		// ��Ʈ���� ������ �ִ� DC
		m_TankPosinSize * m_tFrame_TankPosin.iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		m_TankPosinSize * m_tFrame_TankPosin.iMotion,
		m_TankPosinSize,	// ����� ��Ʈ�� ����
		m_TankPosinSize,	// ����� ��Ʈ�� ����
		RGB(0, 0, 0));	// ������ ���� ��
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

