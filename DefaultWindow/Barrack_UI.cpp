#include "stdafx.h"
#include "Barrack_UI.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
CBarrack_UI::CBarrack_UI()
{
    InsertBmpFile();
}

CBarrack_UI::~CBarrack_UI()
{
    Release();
}

void CBarrack_UI::Initialize()
{
	//처음 크기 고정
	m_tInfo.fCX = 192.f;
	m_tInfo.fCY = 160.f;

	__super::Update_Rect();

	//건물은 애니메이션이 없잖아?
	m_pFrameKey = L"Barrack_UI";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_UI;
}

int CBarrack_UI::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	UpdateMouse();
	return 0;
}

void CBarrack_UI::Late_Update()
{
}

void CBarrack_UI::Render(HDC hDC)
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

void CBarrack_UI::Release()
{
}

void CBarrack_UI::InsertBmpFile()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Building/Barrack/Barrack_UI.bmp", L"Barrack_UI");
}

UIOBJECTTYPE CBarrack_UI::GetType() const
{
	return UI_OBJECT_BUILD;
}

int CBarrack_UI::GetDetailType() const
{
	return UI_STATIC_OBJ_BARRACK;
}
