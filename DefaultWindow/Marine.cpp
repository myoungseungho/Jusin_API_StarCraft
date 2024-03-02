#include "stdafx.h"
#include "Marine.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Marine_Idle_State.h"
#include "Marine_Walk_State.h"
#include "Marine_Attack_State.h"
#include "Marine_Die_State.h"
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
	if (m_CurrentState == NON_STATE)
	{
		m_eRender = RENDER_GAMEOBJECT;

		//처음 크기 고정
		m_tInfo.fCX = 64.f;
		m_tInfo.fCY = 64.f;

		m_vecState.push_back(new CMarine_Idle_State);
		m_vecState.push_back(new CMarine_Walk_State);
		m_vecState.push_back(new CMarine_Attack_State);
		m_vecState.push_back(new CMarine_Die_State);

		ChangeState(IDLE_STATE);

		m_Stat.m_Hp = 40;
		m_Stat.m_Attack = 5;
		m_Stat.m_AttackRange = 130.f;
		m_Stat.m_DetectionRange = 200.f;
		m_Stat.m_fSpeed = 5.f;
		m_Stat.m_MaxHp = 40;
		lstrcpyW(m_Stat.m_Name, L"Marine");
	}
}

int CMarine::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	m_vecState[m_CurrentState]->Update(this);
	return OBJ_NOEVENT;
}

void CMarine::Late_Update()
{
	m_vecState[m_CurrentState]->Late_Update(this);

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

	m_vecState[m_CurrentState]->Render(this, hDC);
}

void CMarine::Release()
{
	for_each(m_vecState.begin(), m_vecState.end(), Safe_Delete<IState*>);
}

void CMarine::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Idle/MARINE_DOWNLEFT.bmp", L"MARINE_DOWNLEFT");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Work/Marine_Walk_Up.bmp", L"Marine_Walk_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Work/Marine_Walk_Up_Right_45.bmp", L"Marine_Walk_Up_Right_45");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Work/Marine_Walk_Right_90.bmp", L"Marine_Walk_Right_90");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Work/Marine_Walk_Down_Right_150.bmp", L"Marine_Walk_Down_Right_150");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Work/Marine_Walk_Down_180.bmp", L"MARINE_WALK_Down_180");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Work/Marine_Walk_Up_Left_120.bmp", L"Marine_Walk_Up_Left_120");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Work/Marine_Walk_Left.bmp", L"Marine_Walk_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Work/Marine_Walk_Down_Left.bmp", L"Marine_Walk_Down_Left");

	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_UP] = (L"Marine_Walk_Up");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_UP],{0,17,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RUP] = (L"Marine_Walk_Up_Right_45");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RUP],{0,17,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RIGHT] = (L"Marine_Walk_Right_90");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RIGHT],{0,17,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RDOWN] = (L"Marine_Walk_Down_Right_150");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RDOWN],{0,17,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_DOWN] = (L"MARINE_WALK_Down_180");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_DOWN],{0,8,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LDOWN] = (L"Marine_Walk_Down_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LDOWN],{0,17,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LEFT] = (L"Marine_Walk_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LEFT],{0,17,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LUP] = (L"Marine_Walk_Up_Left_120");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LEFT],{0,17,0,50,GetTickCount()} });


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Attack/Mairen_Attack_Up.bmp", L"Mairen_Attack_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Attack/Mairen_Attack_Up_Right_45.bmp", L"Mairen_Attack_Up_Right_45");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Attack/Mairen_Attack_Right_90.bmp", L"Mairen_Attack_Right_90");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Attack/Mairen_Attack_Down_Right_150.bmp", L"Mairen_Attack_Down_Right_150");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Attack/Mairen_Attack_Down_180.bmp", L"Mairen_Attack_Down_180");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Attack/Mairen_Attack_Down_Left.bmp", L"Mairen_Attack_Down_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Attack/Mairen_Attack_Left.bmp", L"Mairen_Attack_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Attack/Mairen_Attack_Up_Left_120.bmp", L"Mairen_Attack_Up_Left_120");

	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_UP] = (L"Mairen_Attack_Up");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_UP],{0,5,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RUP] = (L"Mairen_Attack_Up_Right_45");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RUP],{0,5,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RIGHT] = (L"Mairen_Attack_Right_90");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RIGHT],{0,5,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RDOWN] = (L"Mairen_Attack_Down_Right_150");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RDOWN],{0,5,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_DOWN] = (L"Mairen_Attack_Down_180");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_DOWN],{0,2,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LDOWN] = (L"Mairen_Attack_Down_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LDOWN],{0,5,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LEFT] = (L"Mairen_Attack_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LEFT],{0,5,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LUP] = (L"Mairen_Attack_Up_Left_120");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LUP],{0,5,0,50,GetTickCount()} });

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Marine/Die/Marine_Dead.bmp", L"Marine_Dead");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/Tspark/Tspark.bmp", L"Tspark");
}

DYNAMIC_OBJID CMarine::GetType() const
{
	return DYNAMIC_OBJ_MARINE;
}
