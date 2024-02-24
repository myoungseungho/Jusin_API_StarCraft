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

	//ó�� ũ�� ����
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
