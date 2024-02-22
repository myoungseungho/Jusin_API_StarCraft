#include "stdafx.h"
#include "Scv.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "StateMgr.h"
#include "Scv_Idle_State.h"
#include "Scv_Walk_State.h"
#include "Scv_Attack_State.h"
CScv::CScv()
{
	InsertBmpFile();
}

CScv::~CScv()
{
	Release();
}

void CScv::Initialize()
{
	if (m_CurrentState == nullptr)
	{
		IState* IdleState = (*CStateMgr::Get_Instance()->GetVecObjState(OBJ_SCV))[IDLE_STATE];
		m_CurrentState = IdleState;
		ChangeState(IdleState);
	}

	m_eRender = RENDER_GAMEOBJECT;

	//처음 크기 고정
	m_tInfo.fCX = 72.f;
	m_tInfo.fCY = 72.f;
}

int CScv::Update()
{
	__super::Update_Rect();

	m_CurrentState->Update(this);
	return OBJ_NOEVENT;
}

void CScv::Late_Update()
{
	m_CurrentState->Late_Update(this);

	__super::Move_Frame();
}

void CScv::Render(HDC hDC)
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

	m_CurrentState->Render(this, hDC);
}

void CScv::Release()
{
	m_CurrentState->Release(this);
}



void CScv::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Scv/Idle/SCV_IDLE.bmp", L"SCV_IDLE");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Scv/Attack/SCV_ATTACK.bmp", L"SCV_ATTACK");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/ScvAtt/SCV_Bullet.bmp", L"SCV_Bullet");
}
