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
	//	hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
	//	_scv->Get_Rect().left + iScrollX, // 복사 받을 위치 좌표
	//	_scv->Get_Rect().top + iScrollY,
	//	(int)_scv->Get_Info().fCX,	// 복사 받을 이미지의 가로, 세로
	//	(int)_scv->Get_Info().fCY,
	//	hMemDC,		// 비트맵을 가지고 있는 DC
	//	(int)_scv->Get_Info().fCX * m_pFrameCopy->iFrameStart,			// 비트맵 출력 시작 좌표 LEFT, TOP
	//	(int)_scv->Get_Info().fCY * m_pFrameCopy->iMotion,
	//	(int)_scv->Get_Info().fCX,	// 출력할 비트맵 가로
	//	(int)_scv->Get_Info().fCY,	// 출력할 비트맵 세로
	//	RGB(0, 0, 0));	// 제거할 색상 값
}

void CScv_Idle_State::Release(CObj_Dynamic*)
{
}

