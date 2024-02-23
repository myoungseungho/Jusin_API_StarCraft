#include "stdafx.h"
#include "Tank.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "StateMgr.h"
CTank::CTank()
{
	InsertBmpFile();
}

CTank::~CTank()
{
	Release();
}

void CTank::Initialize()
{
	if (m_CurrentState == nullptr)
	{
		IState* IdleState = (*CStateMgr::Get_Instance()->GetVecObjState(DYNAMIC_OBJ_TANK))[IDLE_STATE];
		m_CurrentState = IdleState;
		ChangeState(IdleState);
	}

	m_eRender = RENDER_GAMEOBJECT;

	//처음 크기 고정
	m_tInfo.fCX = 128.f;
	m_tInfo.fCY = 128.f;
}

int CTank::Update()
{
	__super::Update_Rect();

	m_CurrentState->Update(this);
	return OBJ_NOEVENT;
}

void CTank::Late_Update()
{
	m_CurrentState->Late_Update(this);

	__super::Move_Frame();
}

void CTank::Render(HDC hDC)
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

void CTank::Release()
{
	m_CurrentState->Release(this);
}

void CTank::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Lower/Lower_Tank_Walk_Up.bmp", L"Lower_Tank_Walk_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Lower/Lower_Tank_Walk_Up_Right_30.bmp", L"Lower_Tank_Walk_Up_Right_30");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Lower/Lower_Tank_Walk_Up_Right_45.bmp", L"Lower_Tank_Walk_Up_Right_45");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Lower/Lower_Tank_Walk_Up_Right_70.bmp", L"Lower_Tank_Walk_Up_Right_70");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Lower/Lower_Tank_Walk_Right_90.bmp", L"Lower_Tank_Walk_Right_90");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Lower/Lower_Tank_Walk_Down_Right_120.bmp", L"Lower_Tank_Walk_Down_Right_120");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Lower/Lower_Tank_Walk_Down_Right_150.bmp", L"Lower_Tank_Walk_Down_Right_150");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Lower/Lower_Tank_Walk_Down_Right_170.bmp", L"Lower_Tank_Walk_Down_Right_170");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Lower/Lower_Tank_Walk_Down.bmp", L"Lower_Tank_Walk_Down");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Upper/Tank_Upper_Up.bmp", L"Tank_Upper_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Upper/Tank_Upper_Up_Right_30.bmp", L"Tank_Upper_Up_Right_30");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Upper/Tank_Upper_Up_Right_45.bmp", L"Tank_Upper_Up_Right_45");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Upper/Tank_Upper_Up_Right_70.bmp", L"Tank_Upper_Up_Right_70");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Upper/Tank_Upper_Right.bmp", L"Tank_Upper_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Upper/Tank_Upper_Down_Right_120.bmp", L"Tank_Upper_Down_Right_120");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Upper/Tank_Upper_Down_Right_150.bmp", L"Tank_Upper_Down_Right_150");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Upper/Tank_Upper_Down_Right_170.bmp", L"Tank_Upper_Down_Right_170");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Upper/Tank_Upper_Down.bmp", L"Tank_Upper_Down");

}
