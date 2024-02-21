#include "stdafx.h"
#include "Scv_Idle_State.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
CScv_Idle_State::CScv_Idle_State()
{
}

CScv_Idle_State::~CScv_Idle_State()
{
}

void CScv_Idle_State::Initialize(CObj_Dynamic* _scv)
{
	m_pFrameCopy = _scv->Get_Frame();
	m_pFrameKeyCopy = _scv->Get_FrameKey();

	*m_pFrameKeyCopy = L"SCV_IDLE";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 16;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 200;
	m_pFrameCopy->dwTime = GetTickCount();
}

int CScv_Idle_State::Update(CObj_Dynamic*)
{
	return 0;
}

void CScv_Idle_State::Late_Update(CObj_Dynamic* _scv)
{
	//_scv->Move_Frame();
}

void CScv_Idle_State::Render(CObj_Dynamic* _scv, HDC hDC)
{
	//int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKeyCopy);

	//GdiTransparentBlt(
	//	hDC,		// (���� ����)���������� �׸��� �׸� DC ����
	//	_scv->Get_Rect().left + iScrollX, // ���� ���� ��ġ ��ǥ
	//	_scv->Get_Rect().top + iScrollY,
	//	(int)_scv->Get_Info().fCX,	// ���� ���� �̹����� ����, ����
	//	(int)_scv->Get_Info().fCY,
	//	hMemDC,		// ��Ʈ���� ������ �ִ� DC
	//	(int)_scv->Get_Info().fCX * m_pFrameCopy->iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
	//	(int)_scv->Get_Info().fCY * m_pFrameCopy->iMotion,
	//	(int)_scv->Get_Info().fCX,	// ����� ��Ʈ�� ����
	//	(int)_scv->Get_Info().fCY,	// ����� ��Ʈ�� ����
	//	RGB(0, 0, 0));	// ������ ���� ��
}

void CScv_Idle_State::Release(CObj_Dynamic*)
{
}

