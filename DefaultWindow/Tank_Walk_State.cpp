#include "stdafx.h"
#include "Tank_Walk_State.h"
#include "TileMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
CTank_Walk_State::CTank_Walk_State()
{
}

CTank_Walk_State::~CTank_Walk_State()
{
}

void CTank_Walk_State::Initialize(CObj_Dynamic* _tank)
{
	m_pFrameCopy = _tank->Get_Frame();
	m_pFrameKeyCopy = _tank->Get_FrameKey();

	*m_pFrameKeyCopy = L"Lower_Tank_Walk_Right_90";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 5;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 50;
	m_pFrameCopy->dwTime = GetTickCount();

	m_pFrameKey_Attack = L"Tank_Upper_Right";
	m_tFrame_Attack.iFrameStart = 0;
	m_tFrame_Attack.iFrameEnd = 0;
	m_tFrame_Attack.iMotion = 0;
	m_tFrame_Attack.dwSpeed = 50;
	m_tFrame_Attack.dwTime = GetTickCount();

	m_AttackFileSize = 128;
	m_Offset_Attack = 0;

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

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey_Attack);

	GdiTransparentBlt(
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		(_tank->Get_Rect().left + iScrollX) + m_Offset_Attack, // ���� ���� ��ġ ��ǥ
		(_tank->Get_Rect().top + iScrollY) + m_Offset_Attack,
		m_AttackFileSize,	// ���� ���� �̹����� ����, ����
		m_AttackFileSize,
		hMemDC,		// ��Ʈ���� ������ �ִ� DC
		m_AttackFileSize * m_tFrame_Attack.iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		m_AttackFileSize * m_tFrame_Attack.iMotion,
		m_AttackFileSize,	// ����� ��Ʈ�� ����
		m_AttackFileSize,	// ����� ��Ʈ�� ����
		RGB(0, 0, 0));	// ������ ���� ��
}

void CTank_Walk_State::Release(CObj_Dynamic*)
{
}

void CTank_Walk_State::Move_Frame(CObj_Dynamic*)
{
	if (m_tFrame_Attack.dwTime + m_tFrame_Attack.dwSpeed < GetTickCount())
	{
		++m_tFrame_Attack.iFrameStart;

		if (m_tFrame_Attack.iFrameStart > m_tFrame_Attack.iFrameEnd)
		{
			m_tFrame_Attack.iFrameStart = 0;
		}

		m_tFrame_Attack.dwTime = GetTickCount();
	}
}

