#include "stdafx.h"
#include "Nuclear_Effect.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
CNuclear_Effect::CNuclear_Effect()
{
	InsertBmpFile();
}

CNuclear_Effect::~CNuclear_Effect()
{
	Release();
}

void CNuclear_Effect::Initialize()
{
	m_eRender = RENDER_UI;
	m_Collision = COLLISION_NOT;
	//처음 크기 고정
	m_tInfo.fCX = 252.f;
	m_tInfo.fCY = 252.f;

	m_pFrameKey = L"NuclearHit";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 25;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
}

int CNuclear_Effect::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		m_bDead = true;

	__super::Update_Rect();
	return 0;
}

void CNuclear_Effect::Late_Update()
{
	Move_Frame();
}

void CNuclear_Effect::Render(HDC hDC)
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

DYNAMIC_OBJID CNuclear_Effect::GetType() const
{
	return DYNAMIC_OBJ_NUCLEAR_EFFECT;
}

void CNuclear_Effect::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Nuke/NuclearHit.bmp", L"NuclearHit");
}
