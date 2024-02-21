#include "stdafx.h"
#include "Monster.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{

	m_tInfo.fCX = 300.f;
	m_tInfo.fCY = 300.f;

	m_fSpeed = 3.f;
	m_pFrameKey = L"Monster";
	m_eRender = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Monster.bmp", L"Monster");
}

int CMonster::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::Late_Update()
{
	
}

void CMonster::Render(HDC hDC)
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
		0,			// 비트맵 출력 시작 좌표 LEFT, TOP
		0,
		(int)m_tInfo.fCX,	// 출력할 비트맵 가로
		(int)m_tInfo.fCY,	// 출력할 비트맵 세로
		RGB(255, 255, 255));	// 제거할 색상 값
}

void CMonster::Release()
{
}
