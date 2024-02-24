#include "stdafx.h"
#include "Tank.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Tank_Idle_State.h"
#include "Tank_Walk_State.h"
#include "Tank_Attack_State.h"
#include "Tank_Die_State.h"
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
	if (m_CurrentState == NON_STATE)
	{
		m_vecState.push_back(new CTank_Idle_State);
		m_vecState.push_back(new CTank_Walk_State);
		m_vecState.push_back(new CTank_Attack_State);
		m_vecState.push_back(new CTank_Die_State);

		ChangeState(IDLE_STATE);
	}

	m_eRender = RENDER_GAMEOBJECT;

	//ó�� ũ�� ����
	m_tInfo.fCX = 128.f;
	m_tInfo.fCY = 128.f;
}

int CTank::Update()
{
	__super::Update_Rect();

	m_vecState[m_CurrentState]->Update(this);
	return OBJ_NOEVENT;
}

void CTank::Late_Update()
{
	m_vecState[m_CurrentState]->Late_Update(this);

	__super::Move_Frame();
}

void CTank::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		m_tRect.left + iScrollX, // ���� ���� ��ġ ��ǥ
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,	// ���� ���� �̹����� ����, ����
		(int)m_tInfo.fCY,
		hMemDC,		// ��Ʈ���� ������ �ִ� DC
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,	// ����� ��Ʈ�� ����
		(int)m_tInfo.fCY,	// ����� ��Ʈ�� ����
		RGB(0, 0, 0));	// ������ ���� ��

	m_vecState[m_CurrentState]->Render(this, hDC);
}

void CTank::Release()
{
	m_vecState[m_CurrentState]->Release(this);
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

DYNAMIC_OBJID CTank::GetType() const
{
	return DYNAMIC_OBJ_TANK;
}
