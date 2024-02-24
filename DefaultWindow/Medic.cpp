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

	//ó�� ũ�� ����
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
