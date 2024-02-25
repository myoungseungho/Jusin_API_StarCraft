#include "stdafx.h"
#include "Mineral.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CMineral::CMineral()
{
	InsertBmpFile();
}

CMineral::~CMineral()
{
	Release();
}

void CMineral::Initialize()
{
	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 96.f;

	m_pFrameKey = L"Mineral";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_BUILDING;
}

int CMineral::Update()
{
	__super::Update_Rect();

	if (!m_IsInfoUpdate)
	{
		CObj_Static::Initialize();
		m_IsInfoUpdate = true;
	}
	return 0;
}

void CMineral::Late_Update()
{
}

void CMineral::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		m_tRect.left + iScrollX, // 복사 받을 위치 좌표
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,	// 복사 받을 이미지의 가로, 세로
		(int)m_tInfo.fCY,
		hMemDC,		// 비트맵을 가지고 있는 DC
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,			// 비트맵 출력 시작 좌표 LEFT, TOP
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,	// 출력할 비트맵 가로
		(int)m_tInfo.fCY,	// 출력할 비트맵 세로
		RGB(0, 0, 0));	// 제거할 색상 값
}

void CMineral::Release()
{
}

void CMineral::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/map/Resource/Mine/Mineral.BMP", L"Mineral");
}
