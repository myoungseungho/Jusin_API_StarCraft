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
		m_eRender = RENDER_GAMEOBJECT;

		//ó�� ũ�� ����
		m_tInfo.fCX = 128.f;
		m_tInfo.fCY = 128.f;

		m_vecState.push_back(new CTank_Idle_State);
		m_vecState.push_back(new CTank_Walk_State);
		m_vecState.push_back(new CTank_Attack_State);
		m_vecState.push_back(new CTank_Die_State);

		ChangeState(IDLE_STATE);

		m_Stat.m_Hp = 150;
		m_Stat.m_Attack = 30;
		m_Stat.m_AttackRange = 200.f;
		m_Stat.m_DetectionRange = 250.f;
		m_Stat.m_fSpeed = 5.f;
		m_Stat.m_MaxHp = 150;
		lstrcpyW(m_Stat.m_Name, L"Tank");
	}
}

int CTank::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

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
	for_each(m_vecState.begin(), m_vecState.end(), Safe_Delete<IState*>);
}

void CTank::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Lower/Lower_Tank_Walk_Up.bmp", L"Lower_Tank_Walk_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Lower/Lower_Tank_Walk_Up_Right_45.bmp", L"Lower_Tank_Walk_Up_Right_45");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Lower/Lower_Tank_Walk_Right_90.bmp", L"Lower_Tank_Walk_Right_90");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Lower/Lower_Tank_Walk_Down_Right_150.bmp", L"Lower_Tank_Walk_Down_Right_150");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Lower/Lower_Tank_Walk_Down.bmp", L"Lower_Tank_Walk_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Lower/Lower_Tank_Walk_Down_Left.bmp", L"Lower_Tank_Walk_Down_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Lower/Lower_Tank_Walk_Left.bmp", L"Lower_Tank_Walk_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Lower/Lower_Tank_Walk_Up_Left.bmp", L"Lower_Tank_Walk_Up_Left");

	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_UP] = (L"Lower_Tank_Walk_Up");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_UP],{0,5,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RUP] = (L"Lower_Tank_Walk_Up_Right_45");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RUP],{0,5,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RIGHT] = (L"Lower_Tank_Walk_Right_90");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RIGHT],{0,5,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RDOWN] = (L"Lower_Tank_Walk_Down_Right_150");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RDOWN],{0,5,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_DOWN] = (L"Lower_Tank_Walk_Down");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_DOWN],{0,2,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LDOWN] = (L"Lower_Tank_Walk_Down_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LDOWN],{0,5,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LEFT] = (L"Lower_Tank_Walk_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LEFT],{0,5,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LUP] = (L"Lower_Tank_Walk_Up_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LUP],{0,5,0,50,GetTickCount()} });

	//���ݸ��
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_UP] = (L"Lower_Tank_Walk_Up");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_UP],{0,5,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RUP] = (L"Lower_Tank_Walk_Up_Right_45");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RUP],{0,5,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RIGHT] = (L"Lower_Tank_Walk_Right_90");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RIGHT],{0,5,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RDOWN] = (L"Lower_Tank_Walk_Down_Right_150");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RDOWN],{0,5,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_DOWN] = (L"Lower_Tank_Walk_Down");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_DOWN],{0,2,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LDOWN] = (L"Lower_Tank_Walk_Down_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LDOWN],{0,5,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LEFT] = (L"Lower_Tank_Walk_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LEFT],{0,5,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LUP] = (L"Lower_Tank_Walk_Up_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LUP],{0,5,0,50,GetTickCount()} });


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Upper/Tank_Upper_Up.bmp", L"Tank_Upper_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Upper/Tank_Upper_Up_Right_45.bmp", L"Tank_Upper_Up_Right_45");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Upper/Tank_Upper_Right.bmp", L"Tank_Upper_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Upper/Tank_Upper_Down_Right_150.bmp", L"Tank_Upper_Down_Right_150");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Upper/Tank_Upper_Down.bmp", L"Tank_Upper_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Upper/Tank_Upper_Down_Left.bmp", L"Tank_Upper_Down_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Upper/Tank_Upper_Left.bmp", L"Tank_Upper_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Tank/Upper/Tank_Upper_Up_Left.bmp", L"Tank_Upper_Up_Left");

	m_KeyAndFrame.m_FrameTankPosinKey[DIR_UP] = (L"Tank_Upper_Up");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameTankPosinKey[DIR_UP],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameTankPosinKey[DIR_RUP] = (L"Tank_Upper_Up_Right_45");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameTankPosinKey[DIR_RUP],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameTankPosinKey[DIR_RIGHT] = (L"Tank_Upper_Right");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameTankPosinKey[DIR_RIGHT],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameTankPosinKey[DIR_RDOWN] = (L"Tank_Upper_Down_Right_150");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameTankPosinKey[DIR_RDOWN],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameTankPosinKey[DIR_DOWN] = (L"Tank_Upper_Down");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameTankPosinKey[DIR_DOWN],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameTankPosinKey[DIR_LDOWN] = (L"Tank_Upper_Down_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameTankPosinKey[DIR_LDOWN],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameTankPosinKey[DIR_LEFT] = (L"Tank_Upper_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameTankPosinKey[DIR_LEFT],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameTankPosinKey[DIR_LUP] = (L"Tank_Upper_Up_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameTankPosinKey[DIR_LUP],{0,0,0,50,GetTickCount()} });


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Tanklaunch/TankLaunch_Up.bmp", L"TankLaunch_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Tanklaunch/TankLaunch_Up_Right.bmp", L"TankLaunch_Up_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Tanklaunch/TankLaunch_Right.bmp", L"TankLaunch_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Tanklaunch/TankLaunch_Down_Right.bmp", L"TankLaunch_Down_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Tanklaunch/TankLaunch_Down.bmp", L"TankLaunch_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Tanklaunch/TankLaunch_Down_Left.bmp", L"TankLaunch_Down_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Tanklaunch/TankLaunch_Left.bmp", L"TankLaunch_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Tanklaunch/TankLaunch_Up_Left.bmp", L"TankLaunch_Up_Left");

	m_KeyAndFrame.m_FrameTankPosinLaunchKey[DIR_UP] = (L"TankLaunch_Up");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameTankPosinLaunchKey[DIR_UP],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameTankPosinLaunchKey[DIR_RUP] = (L"TankLaunch_Up_Right");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameTankPosinLaunchKey[DIR_RUP],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameTankPosinLaunchKey[DIR_RIGHT] = (L"TankLaunch_Right");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameTankPosinLaunchKey[DIR_RIGHT],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameTankPosinLaunchKey[DIR_RDOWN] = (L"TankLaunch_Down_Right");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameTankPosinLaunchKey[DIR_RDOWN],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameTankPosinLaunchKey[DIR_DOWN] = (L"TankLaunch_Down");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameTankPosinLaunchKey[DIR_DOWN],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameTankPosinLaunchKey[DIR_LDOWN] = (L"TankLaunch_Down_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameTankPosinLaunchKey[DIR_LDOWN],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameTankPosinLaunchKey[DIR_LEFT] = (L"TankLaunch_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameTankPosinLaunchKey[DIR_LEFT],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameTankPosinLaunchKey[DIR_LUP] = (L"TankLaunch_Up_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameTankPosinLaunchKey[DIR_LUP],{0,0,0,50,GetTickCount()} });

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/TankHit/TankHit.bmp", L"TankHit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Bang2/Tank_BANG.bmp", L"Tank_BANG");
}

DYNAMIC_OBJID CTank::GetType() const
{
	return DYNAMIC_OBJ_TANK;
}
