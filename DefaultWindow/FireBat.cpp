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

		//ó�� ũ�� ����
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
		m_Stat.m_MaxHp = 50.f;
		lstrcpyW(m_Stat.m_Name, L"FireBat");
	}
}

int CFireBat::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

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

void CFireBat::Release()
{
	for_each(m_vecState.begin(), m_vecState.end(), Safe_Delete<IState*>);
}

void CFireBat::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Idle/Firebat_Idle.bmp", L"Firebat_Idle");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Work/Firebat_Work_Up.bmp", L"Firebat_Work_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Work/Firebat_Work_Up_Right_60.bmp", L"Firebat_Work_Up_Right_60");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Work/Firebat_Work_Up_Right_90.bmp", L"Firebat_Work_Up_Right_90");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Work/Firebat_Work_Down_Right_150.bmp", L"Firebat_Work_Down_Right_150");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Work/Firebat_Work_Down.bmp", L"Firebat_Work_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Work/Firebat_Work_Down_Left.bmp", L"Firebat_Work_Down_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Work/Firebat_Work_Left.bmp", L"Firebat_Work_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Work/Firebat_Work_Up_Left.bmp", L"Firebat_Work_Up_Left");

	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_UP] = (L"Firebat_Work_Up");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_UP],{0,15,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RUP] = (L"Firebat_Work_Up_Right_60");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RUP],{0,15,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RIGHT] = (L"Firebat_Work_Up_Right_90");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RIGHT],{0,15,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RDOWN] = (L"Firebat_Work_Down_Right_150");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RDOWN],{0,15,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_DOWN] = (L"Firebat_Work_Down");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_DOWN],{0,7,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LDOWN] = (L"Firebat_Work_Down_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LDOWN],{0,7,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LEFT] = (L"Firebat_Work_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LEFT],{0,9,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LUP] = (L"Firebat_Work_Up_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LUP],{0,15,0,50,GetTickCount()} });


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Attack/Firebat_Attack_Up.bmp", L"Firebat_Attack_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Attack/Firebat_Attack_Up_Right_45.bmp", L"Firebat_Attack_Up_Right_45");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Attack/Firebat_Attack_Right_90.bmp", L"Firebat_Attack_Right_90");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Attack/Firebat_Attack_Down_Right_150.bmp", L"Firebat_Attack_Down_Right_150");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Attack/Firebat_Attack_Down.bmp", L"Firebat_Attack_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Attack/Firebat_Attack_Down_Left.bmp", L"Firebat_Attack_Down_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Attack/Firebat_Attack_Left.bmp", L"Firebat_Attack_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Firebat/Attack/Firebat_Attack_Up_Left.bmp", L"Firebat_Attack_Up_Left");

	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_UP] = (L"Firebat_Attack_Up");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_UP],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RUP] = (L"Firebat_Attack_Up_Right_45");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RUP],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RIGHT] = (L"Firebat_Attack_Right_90");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RIGHT],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RDOWN] = (L"Firebat_Attack_Down_Right_150");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RDOWN],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_DOWN] = (L"Firebat_Attack_Down");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_DOWN],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LDOWN] = (L"Firebat_Attack_Down_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LDOWN],{0,1,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LEFT] = (L"Firebat_Attack_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LEFT],{0,1,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LUP] = (L"Firebat_Attack_Up_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LUP],{0,1,0,50,GetTickCount()} });

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/FirebatAtt/FireBat_Bullet_Up.bmp", L"FireBat_Bullet_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/FirebatAtt/FireBat_Bullet_Up_Right_45.bmp", L"FireBat_Bullet_Up_Right_45");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/FirebatAtt/FireBat_Bullet_Right.bmp", L"FireBat_Bullet_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/FirebatAtt/FireBat_Bullet_Down_Right_150.bmp", L"FireBat_Bullet_Down_Right_150");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/FirebatAtt/FireBat_Bullet_Down.bmp", L"FireBat_Bullet_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/FirebatAtt/FireBat_Bullet_Down_Left.bmp", L"FireBat_Bullet_Down_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/FirebatAtt/FireBat_Bullet_Left.bmp", L"FireBat_Bullet_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/FirebatAtt/FireBat_Bullet_Up_Left.bmp", L"FireBat_Bullet_Up_Left");

	m_KeyAndFrame.m_FrameBulletAttackKey[DIR_UP] = (L"FireBat_Bullet_Up");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameBulletAttackKey[DIR_UP],{0,11,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameBulletAttackKey[DIR_RUP] = (L"FireBat_Bullet_Up_Right_45");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameBulletAttackKey[DIR_RUP],{0,11,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameBulletAttackKey[DIR_RIGHT] = (L"FireBat_Bullet_Right");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameBulletAttackKey[DIR_RIGHT],{0,11,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameBulletAttackKey[DIR_RDOWN] = (L"FireBat_Bullet_Down_Right_150");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameBulletAttackKey[DIR_RDOWN],{0,11,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameBulletAttackKey[DIR_DOWN] = (L"FireBat_Bullet_Down");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameBulletAttackKey[DIR_DOWN],{0,11,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameBulletAttackKey[DIR_LDOWN] = (L"FireBat_Bullet_Down_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameBulletAttackKey[DIR_LDOWN],{0,11,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameBulletAttackKey[DIR_LEFT] = (L"FireBat_Bullet_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameBulletAttackKey[DIR_LEFT],{0,11,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameBulletAttackKey[DIR_LUP] = (L"FireBat_Bullet_Up_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameBulletAttackKey[DIR_LUP],{0,11,0,50,GetTickCount()} });

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Bang0/FireBat_Die.bmp", L"FireBat_Die");
}

DYNAMIC_OBJID CFireBat::GetType() const
{
	return DYNAMIC_OBJ_FIREBAT;
}
