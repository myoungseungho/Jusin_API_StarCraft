#include "stdafx.h"
#include "FireBat.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "StateMgr.h"

CFireBat::CFireBat() : m_CurrentState(nullptr)
{
	InsertBmpFile();
}

CFireBat::~CFireBat()
{
	Release();
}

void CFireBat::Initialize()
{
	if (m_CurrentState == nullptr)
	{
		IState* IdleState = (*CStateMgr::Get_Instance()->GetVecObjState(OBJ_FIREBAT))[IDLE_STATE];
		m_CurrentState = IdleState;
		ChangeState(IdleState);
	}

	m_eRender = RENDER_GAMEOBJECT;

	//ó�� ũ�� ����
	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;
}

int CFireBat::Update()
{
	__super::Update_Rect();

	m_CurrentState->Update(this);
	return OBJ_NOEVENT;
}

void CFireBat::Late_Update()
{
	m_CurrentState->Late_Update(this);

	__super::Move_Frame();
}

void CFireBat::Render(HDC hDC)
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

	m_CurrentState->Render(this, hDC);
}

void CFireBat::Release()
{
	m_CurrentState->Release(this);
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
