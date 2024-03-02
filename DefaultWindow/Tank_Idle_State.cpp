#include "stdafx.h"
#include "Tank_Idle_State.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
CTank_Idle_State::CTank_Idle_State()
{
}

CTank_Idle_State::~CTank_Idle_State()
{
}

void CTank_Idle_State::Initialize(CObj_Dynamic* _tank)
{
	m_pFrameCopy = _tank->Get_Frame();
	m_pFrameKeyCopy = _tank->Get_FrameKey();

	*m_pFrameKeyCopy = L"Lower_Tank_Walk_Right_90";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 5;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 100;
	m_pFrameCopy->dwTime = GetTickCount();

	m_pFrameKey_TankPosin = L"Tank_Upper_Right";
	m_tFrame_TankPosin.iFrameStart = 0;
	m_tFrame_TankPosin.iFrameEnd = 0;
	m_tFrame_TankPosin.iMotion = 0;
	m_tFrame_TankPosin.dwSpeed = 50;
	m_tFrame_TankPosin.dwTime = GetTickCount();

	m_TankPosinSize = 128;

	if (_tank->Get_Stat().m_Hp < 0)
		_tank->ChangeState(DIE_STATE);
}

int CTank_Idle_State::Update(CObj_Dynamic* _tank)
{
	if (m_dwTime + 1000 < GetTickCount())
	{
		_tank->CheckEnemy();
		m_dwTime = GetTickCount();
	}
	return 0;
}

void CTank_Idle_State::Late_Update(CObj_Dynamic* _tank)
{
	Move_Frame(_tank);
}

void CTank_Idle_State::Render(CObj_Dynamic* _tank, HDC hDC)
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

void CTank_Idle_State::Release(CObj_Dynamic*)
{
}

void CTank_Idle_State::Move_Frame(CObj_Dynamic*)
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
