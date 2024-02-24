#include "stdafx.h"
#include "Medic.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Medic_Idle_State.h"
#include "Medic_Walk_State.h"
#include "Medic_Attack_State.h"
#include "Medic_Die_State.h"
CMedic::CMedic()
{
	InsertBmpFile();
}

CMedic::~CMedic()
{
	Release();
}

void CMedic::Initialize()
{
	if (m_CurrentState == nullptr)
	{
		m_vecState.push_back(new CMedic_Idle_State);
		m_vecState.push_back(new CMedic_Walk_State);
		m_vecState.push_back(new CMedic_Attack_State);
		m_vecState.push_back(new CMedic_Die_State);

		ChangeState(m_vecState[IDLE_STATE]);
	}

	m_eRender = RENDER_GAMEOBJECT;

	//처음 크기 고정
	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 64.f;
}

int CMedic::Update()
{
	__super::Update_Rect();

	m_CurrentState->Update(this);
	return OBJ_NOEVENT;
}

void CMedic::Late_Update()
{
	m_CurrentState->Late_Update(this);

	__super::Move_Frame();
}

void CMedic::Render(HDC hDC)
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

void CMedic::Release()
{
	m_CurrentState->Release(this);
}

void CMedic::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Idle/Medic_Idle.bmp", L"Medic_Idle");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Work/Medic_Walk_Up.bmp", L"Medic_Walk_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Work/Medic_Walk_Up_Right_30.bmp", L"Medic_Walk_Up_Right_30");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Work/Medic_Walk_Up_Right_60.bmp", L"Medic_Walk_Up_Right_60");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Work/Medic_Walk_Right_90.bmp", L"Medic_Walk_Right_90");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Work/Medic_Walk_Down_Right_120.bmp", L"Medic_Walk_Down_Right_120");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Work/Medic_Walk_Down_Right_150.bmp", L"Medic_Walk_Down_Right_150");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Work/Medic_Walk_Down_Right_160.bmp", L"Medic_Walk_Down_Right_160");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Work/Medic_Walk_Down_Right_170.bmp", L"Medic_Walk_Down_Right_170");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Work/Medic_Walk_Down.bmp", L"Medic_Walk_Down");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Attack/Medic_Attack_Up.bmp", L"Medic_Attack_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Attack/Medic_Attack_Up_Right_30.bmp", L"Medic_Attack_Up_Right_30");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Attack/Medic_Attack_Up_Right_45.bmp", L"Medic_Attack_Up_Right_45");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Attack/Medic_Attack_Up_Right_60.bmp", L"Medic_Attack_Up_Right_60");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Attack/Medic_Attack_Up_Right_60.bmp", L"Medic_Attack_Up_Right_60");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Attack/Medic_Attack_Right.bmp", L"Medic_Attack_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Attack/Medic_Attack_Down_Right_150.bmp", L"Medic_Attack_Down_Right_150");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Attack/Medic_Attack_Down_Right_170.bmp", L"Medic_Attack_Down_Right_170");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Attack/Medic_Attack_Down_Right_170.bmp", L"Medic_Attack_Down_Right_170");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Die/Medic_Die.bmp", L"Medic_Die");
}

DYNAMIC_OBJID CMedic::GetType() const
{
	return DYNAMIC_OBJ_MEDIC;
}
