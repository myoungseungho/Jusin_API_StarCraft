#include "stdafx.h"
#include "FireBat.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "FireBat_Idle_State.h"
#include "FireBat_Walk_State.h"
#include "FireBat_Attack_State.h"
#include "FireBat_Die_State.h"

CFireBat::CFireBat()
{
	InsertBmpFile();
}

CFireBat::~CFireBat()
{
	Release();
}

void CFireBat::Initialize()
{
	if (m_CurrentState == NON_STATE)
	{
		m_eRender = RENDER_GAMEOBJECT;

		//처음 크기 고정
		m_tInfo.fCX = 32.f;
		m_tInfo.fCY = 32.f;

		m_vecState.push_back(new CFireBat_Idle_State);
		m_vecState.push_back(new CFireBat_Walk_State);
		m_vecState.push_back(new CFireBat_Attack_State);
		m_vecState.push_back(new CFireBat_Die_State);

		ChangeState(IDLE_STATE);

		m_Stat.m_Hp = 50.f;
		m_Stat.m_Attack = 16.f;
		m_Stat.m_AttackRange = 50.f;
		m_Stat.m_DetectionRange = 250.f;
		m_Stat.m_fSpeed = 5.f;
	}
}

int CFireBat::Update()
{
	__super::Update_Rect();

	m_vecState[m_CurrentState]->Update(this);
	return OBJ_NOEVENT;
}

void CFireBat::Late_Update()
{
	m_vecState[m_CurrentState]->Late_Update(this);

	__super::Move_Frame();
}

void CFireBat::Render(HDC hDC)
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

void CFireBat::Release()
{
	m_vecState[m_CurrentState]->Release(this);
}

void CFireBat::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Idle/Firebat_Idle.bmp", L"Firebat_Idle");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Work/Firebat_Work_Up.bmp", L"Firebat_Work_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Work/Firebat_Work_Up_Right_30.bmp", L"Firebat_Work_Up_Right_30");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Work/Firebat_Work_Up_Right_60.bmp", L"Firebat_Work_Up_Right_60");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Work/Firebat_Work_Up_Right_70.bmp", L"Firebat_Work_Up_Right_70");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Work/Firebat_Work_Up_Right_90.bmp", L"Firebat_Work_Up_Right_90");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Work/Firebat_Work_Down_Right_120.bmp", L"Firebat_Work_Down_Right_120");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Work/Firebat_Work_Down_Right_150.bmp", L"Firebat_Work_Down_Right_150");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Work/Firebat_Work_Down_Right_170.bmp", L"Firebat_Work_Down_Right_170");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Work/Firebat_Work_Down.bmp", L"Firebat_Work_Down");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Attack/Firebat_Attack_Up.bmp", L"Firebat_Attack_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Attack/Firebat_Attack_Up_Right_30.bmp", L"Firebat_Attack_Up_Right_30");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Attack/Firebat_Attack_Up_Right_45.bmp", L"Firebat_Attack_Up_Right_45");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Attack/Firebat_Attack_Up_Right_70.bmp", L"Firebat_Attack_Up_Right_70");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Attack/Firebat_Attack_Right_90.bmp", L"Firebat_Attack_Right_90");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Attack/Firebat_Attack_Down_Right_120.bmp", L"Firebat_Attack_Down_Right_120");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Attack/Firebat_Attack_Down_Right_150.bmp", L"Firebat_Attack_Down_Right_150");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Attack/Firebat_Attack_Down_Right_170.bmp", L"Firebat_Attack_Down_Right_170");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Attack/Firebat_Attack_Down.bmp", L"Firebat_Attack_Down");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/FirebatAtt/FireBat_Bullet_Up.bmp", L"FireBat_Bullet_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/FirebatAtt/FireBat_Bullet_Up_Right_30.bmp", L"FireBat_Bullet_Up_Right_30");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/FirebatAtt/FireBat_Bullet_Up_Right_45.bmp", L"FireBat_Bullet_Up_Right_45");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/FirebatAtt/FireBat_Bullet_Up_Right_60.bmp", L"FireBat_Bullet_Up_Right_60");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/FirebatAtt/FireBat_Bullet_Right.bmp", L"FireBat_Bullet_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/FirebatAtt/FireBat_Bullet_Down_Right_120.bmp", L"FireBat_Bullet_Down_Right_120");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/FirebatAtt/FireBat_Bullet_Down_Right_150.bmp", L"FireBat_Bullet_Down_Right_150");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/FirebatAtt/FireBat_Bullet_Down_Right_170.bmp", L"FireBat_Bullet_Down_Right_170");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/FirebatAtt/FireBat_Bullet_Down.bmp", L"FireBat_Bullet_Down");
}

DYNAMIC_OBJID CFireBat::GetType() const
{
	return DYNAMIC_OBJ_FIREBAT;
}
