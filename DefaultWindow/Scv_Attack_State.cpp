#include "stdafx.h"
#include "Scv_Attack_State.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
CScv_Attack_State::CScv_Attack_State() :m_AttackFileSize(0), m_pFrameKey_Attack(nullptr), m_Offset_Attack(0)
{
}

CScv_Attack_State::~CScv_Attack_State()
{
}

void CScv_Attack_State::Initialize(CObj_Dynamic* _scv)
{
	m_pFrameCopy = _scv->Get_Frame();
	m_pFrameKeyCopy = _scv->Get_FrameKey();

	*m_pFrameKeyCopy = L"SCV_ATTACK";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 33;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 200;
	m_pFrameCopy->dwTime = GetTickCount();

	m_pFrameKey_Attack = L"SCV_Bullet";
	m_tFrame_Attack.iFrameStart = 0;
	m_tFrame_Attack.iFrameEnd = 9;
	m_tFrame_Attack.iMotion = 0;
	m_tFrame_Attack.dwSpeed = 50;
	m_tFrame_Attack.dwTime = GetTickCount();

	m_AttackFileSize = 48;
	m_Offset_Attack = 30;
}

int CScv_Attack_State::Update(CObj_Dynamic* _scv)
{
	return 0;
}

void CScv_Attack_State::Late_Update(CObj_Dynamic* _scv)
{
	Move_Frame();
}

void CScv_Attack_State::Render(CObj_Dynamic* _scv, HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey_Attack);

	GdiTransparentBlt(
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		(_scv->Get_Rect().left + iScrollX) + m_Offset_Attack, // 복사 받을 위치 좌표
		(_scv->Get_Rect().top + iScrollY),
		m_AttackFileSize,	// 복사 받을 이미지의 가로, 세로
		m_AttackFileSize,
		hMemDC,		// 비트맵을 가지고 있는 DC
		m_AttackFileSize * m_tFrame_Attack.iFrameStart,			// 비트맵 출력 시작 좌표 LEFT, TOP
		m_AttackFileSize * m_tFrame_Attack.iMotion,
		m_AttackFileSize,	// 출력할 비트맵 가로
		m_AttackFileSize,	// 출력할 비트맵 세로
		RGB(0, 0, 0));	// 제거할 색상 값
}

void CScv_Attack_State::Release(CObj_Dynamic* _scv)
{
}

void CScv_Attack_State::Move_Frame()
{
	if (m_tFrame_Attack.dwTime + m_tFrame_Attack.dwSpeed < GetTickCount())
	{
		++m_tFrame_Attack.iFrameStart;

		if (m_tFrame_Attack.iFrameStart > m_tFrame_Attack.iFrameEnd)
			m_tFrame_Attack.iFrameStart = 0;

		m_tFrame_Attack.dwTime = GetTickCount();
	}
}
