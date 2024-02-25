#include "stdafx.h"
#include "Tile.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CTile::CTile() : m_iDrawID(0), m_iOption(0)
{
}

CTile::~CTile()
{
	Release();
}

void CTile::Initialize()
{
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;
	m_eRender = RENDER_BACKGROUND;
}

int CTile::Update()
{
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CTile::Late_Update()
{
}

void CTile::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Grid");

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		m_tRect.left + iScrollX, // 복사 받을 위치 좌표
		m_tRect.top + iScrollY,
		TILECX,	// 복사 받을 이미지의 가로, 세로
		TILECY,
		hMemDC,		// 비트맵을 가지고 있는 DC
		TILECX * m_iDrawID,			// 비트맵 출력 시작 좌표 LEFT, TOP
		0,
		TILECX,	// 출력할 비트맵 가로
		TILECY,	// 출력할 비트맵 세로
		RGB(255, 255, 255));	// 제거할 색상 값
}

void CTile::Release()
{
}
