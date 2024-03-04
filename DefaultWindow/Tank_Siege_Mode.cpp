#include "stdafx.h"
#include "Tank_Siege_Mode.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
CTank_Siege_Mode::CTank_Siege_Mode() : m_bIdleReady(false)
{
}

CTank_Siege_Mode::~CTank_Siege_Mode()
{
}

void CTank_Siege_Mode::Initialize(CObj_Dynamic* _tank)
{
	m_pFrameCopy = _tank->Get_Frame();
	m_pFrameKeyCopy = _tank->Get_FrameKey();

	*m_pFrameKeyCopy = L"Lower_STank_On";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 5;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 200;
	m_pFrameCopy->dwTime = GetTickCount();


	m_pFrameKey_SiegeOn = L"Upper_STank_On";
	m_tFrame_SiegeOn.iFrameStart = 0;
	m_tFrame_SiegeOn.iFrameEnd = 4;
	m_tFrame_SiegeOn.iMotion = 0;
	m_tFrame_SiegeOn.dwSpeed = 200;
	m_tFrame_SiegeOn.dwTime = GetTickCount();

	m_pFrameKey_SiegeOff = L"Upper_STank_Off";
	m_tFrame_SiegeOff.iFrameStart = 0;
	m_tFrame_SiegeOff.iFrameEnd = 4;
	m_tFrame_SiegeOff.iMotion = 0;
	m_tFrame_SiegeOff.dwSpeed = 200;
	m_tFrame_SiegeOff.dwTime = GetTickCount();
}

int CTank_Siege_Mode::Update(CObj_Dynamic*)
{
	return 0;
}

void CTank_Siege_Mode::Late_Update(CObj_Dynamic* _tank)
{
	Move_Frame(_tank);
}

void CTank_Siege_Mode::Render(CObj_Dynamic* _tank, HDC hDC)
{
	if (!_tank->GetBoolSiegeMode())
		return;

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = nullptr;
	if (m_bIdleReady)
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey_SiegeOff);
		GdiTransparentBlt(
			hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
			_tank->Get_Rect().left + iScrollX - 12.f, // 복사 받을 위치 좌표
			_tank->Get_Rect().top + iScrollY - 12.f,
			(int)_tank->Get_Info().fCX,	// 복사 받을 이미지의 가로, 세로
			(int)_tank->Get_Info().fCY,
			hMemDC,		// 비트맵을 가지고 있는 DC
			(int)_tank->Get_Info().fCX * m_tFrame_SiegeOff.iFrameStart,			// 비트맵 출력 시작 좌표 LEFT, TOP
			(int)_tank->Get_Info().fCY * m_tFrame_SiegeOff.iMotion,
			(int)_tank->Get_Info().fCX,	// 출력할 비트맵 가로
			(int)_tank->Get_Info().fCY,	// 출력할 비트맵 세로
			RGB(0, 0, 0));	// 제거할 색상 값
	}
	else
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey_SiegeOn);
		GdiTransparentBlt(
			hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
			_tank->Get_Rect().left + iScrollX - 12.f, // 복사 받을 위치 좌표
			_tank->Get_Rect().top + iScrollY - 12.f,
			(int)_tank->Get_Info().fCX,	// 복사 받을 이미지의 가로, 세로
			(int)_tank->Get_Info().fCY,
			hMemDC,		// 비트맵을 가지고 있는 DC
			(int)_tank->Get_Info().fCX * m_tFrame_SiegeOn.iFrameStart,			// 비트맵 출력 시작 좌표 LEFT, TOP
			(int)_tank->Get_Info().fCY * m_tFrame_SiegeOn.iMotion,
			(int)_tank->Get_Info().fCX,	// 출력할 비트맵 가로
			(int)_tank->Get_Info().fCY,	// 출력할 비트맵 세로
			RGB(0, 0, 0));	// 제거할 색상 값
	}
}

void CTank_Siege_Mode::Release(CObj_Dynamic*)
{
}

void CTank_Siege_Mode::Move_Frame(CObj_Dynamic* _tank)
{
	if (_tank->GetBoolSiegeMode())
	{
		if (m_bIdleReady)
		{
			if (m_tFrame_SiegeOff.dwTime + m_tFrame_SiegeOff.dwSpeed < GetTickCount())
			{
				++m_tFrame_SiegeOff.iFrameStart;

				if (m_tFrame_SiegeOff.iFrameStart > m_tFrame_SiegeOff.iFrameEnd)
				{
					m_tFrame_SiegeOff.iFrameStart = 0;
					*m_pFrameKeyCopy = L"Lower_STank_Off";
					m_pFrameCopy->iFrameStart = 0;
					m_pFrameCopy->iFrameEnd = 5;
					m_pFrameCopy->iMotion = 0;
					m_pFrameCopy->dwSpeed = 200;
					m_pFrameCopy->dwTime = GetTickCount();
					m_bIdleReady = false;
					_tank->SetBoolSiegeMode(false);
				}

				m_tFrame_SiegeOff.dwTime = GetTickCount();
			}
		}
		else
			if (m_tFrame_SiegeOn.dwTime + m_tFrame_SiegeOn.dwSpeed < GetTickCount())
			{
				++m_tFrame_SiegeOn.iFrameStart;

				if (m_tFrame_SiegeOn.iFrameStart > m_tFrame_SiegeOn.iFrameEnd)
				{
					m_tFrame_SiegeOn.iFrameStart = m_tFrame_SiegeOn.iFrameEnd;
				}

				m_tFrame_SiegeOn.dwTime = GetTickCount();
			}
	}
}

void CTank_Siege_Mode::SetDefaultMode()
{
	m_bIdleReady = true;

	*m_pFrameKeyCopy = L"Lower_STank_Off";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 5;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 200;
	m_pFrameCopy->dwTime = GetTickCount();
}
