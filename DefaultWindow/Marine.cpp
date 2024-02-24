#include "stdafx.h"
#include "Marine.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "StateMgr.h"

CMarine::CMarine()
{
	InsertBmpFile();
}

CMarine::~CMarine()
{
	Release();
}

void CMarine::Initialize()
{
	if (m_CurrentState == nullptr)
	{
		ChangeStateByType(IDLE_STATE);
	}

	m_eRender = RENDER_GAMEOBJECT;

	//처음 크기 고정
	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 64.f;
}

int CMarine::Update()
{
	__super::Update_Rect();

	m_CurrentState->Update(this);
	return OBJ_NOEVENT;
}

void CMarine::Late_Update()
{
	m_CurrentState->Late_Update(this);

	__super::Move_Frame();
}

void CMarine::Render(HDC hDC)
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

void CMarine::Release()
{
	m_CurrentState->Release(this);
}

void CMarine::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Idle/Marine_Idle.bmp", L"Marine_Idle");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Work/Marine_Walk_Up.bmp", L"Marine_Walk_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Work/Marine_Walk_Up_Right_15.bmp", L"Marine_Walk_Up_Right_15");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Work/Marine_Walk_Up_Right_40.bmp", L"Marine_Walk_Up_Right_40");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Work/Marine_Walk_Up_Right_45.bmp", L"Marine_Walk_Up_Right_45");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Work/Marine_Walk_Right_90.bmp", L"Marine_Walk_Right_90");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Work/Marine_Walk_Down_Right_120.bmp", L"Marine_Walk_Down_Right_120");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Work/Marine_Walk_Down_Right_150.bmp", L"Marine_Walk_Down_Right_150");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Work/Marine_Walk_Down_Right_170.bmp", L"Marine_Walk_Down_Right_170");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Work/Marine_Walk_Down_180.bmp", L"MARINE_WALK_Down_180");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Attack/Mairen_Attack_Up.bmp", L"Mairen_Attack_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Attack/Mairen_Attack_Up_Right_45.bmp", L"Mairen_Attack_Up_Right_45");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Attack/Mairen_Attack_Up_Right_70.bmp", L"Mairen_Attack_Up_Right_70");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Attack/Mairen_Attack_Right_90.bmp", L"Mairen_Attack_Right_90");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Attack/Mairen_Attack_Down_Right_120.bmp", L"Mairen_Attack_Down_Right_120");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Attack/Mairen_Attack_Down_Right_135.bmp", L"Mairen_Attack_Down_Right_135");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Attack/Mairen_Attack_Down_Right_150.bmp", L"Mairen_Attack_Down_Right_150");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Attack/Mairen_Attack_Down_Right_170.bmp", L"Mairen_Attack_Down_Right_170");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Attack/Mairen_Attack_Down_180.bmp", L"Mairen_Attack_Down_180");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Die/Marine_Dead.bmp", L"Marine_Dead");
}

DYNAMIC_OBJID CMarine::GetType() const
{
	return DYNAMIC_OBJ_MARINE;
}
