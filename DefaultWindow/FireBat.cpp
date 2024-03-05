#include "stdafx.h"
#include "FireBat.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "FireBat_Idle_State.h"
#include "FireBat_Walk_State.h"
#include "FireBat_Attack_State.h"
#include "FireBat_Die_State.h"
#include "SpawnMgr.h"
#include "UI_FireBat_Display.h"
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
		m_Stat.m_DetectionRange = 200.f;
		m_Stat.m_fSpeed = 3.f;
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

	if (m_bCliecked && m_DisPlayCopy == nullptr)
	{
		m_DisPlayCopy = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_FireBat_Display>(UI_OBJECT_DISPLAY);
	}
	else if (!m_bCliecked && m_DisPlayCopy != nullptr)
	{
		CObjMgr::Get_Instance()->Delete_ID_UIObj(UI_OBJECT_DISPLAY);
		m_DisPlayCopy = nullptr;
	}

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

	int grade = m_Stat.m_MaxHp / 6;
	int currentGrade = m_Stat.m_Hp / grade;
	int frame = currentGrade == 0 ? 5 : currentGrade == 1 ? 5 : currentGrade == 2 ? 4 : currentGrade == 3 ? 3
		: currentGrade == 4 ? 2 : currentGrade == 5 ? 1 : currentGrade == 6 ? 0 : 0;

	HDC	hhpDC = CBmpMgr::Get_Instance()->Find_Image(L"Small_Hp");

	GdiTransparentBlt(
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		m_tRect.left + iScrollX, // 복사 받을 위치 좌표
		m_tRect.top + iScrollY + (int)m_tInfo.fCY + 5.f,
		32,	// 복사 받을 이미지의 가로, 세로
		5,
		hhpDC,		// 비트맵을 가지고 있는 DC
		32 * frame,			// 비트맵 출력 시작 좌표 LEFT, TOP
		5 * m_tFrame.iMotion,
		32,	// 출력할 비트맵 가로
		5,	// 출력할 비트맵 세로
		RGB(0, 0, 0));	// 제거할 색상 값

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

	if (!m_bCliecked)
		return;

	HDC	hSelectDC = nullptr;
	if (this->Get_FactionState() == FACTION_ALLY)
		hSelectDC = CBmpMgr::Get_Instance()->Find_Image(L"PSelect2");
	else if (this->Get_FactionState() == FACTION_ENEMY)
		hSelectDC = CBmpMgr::Get_Instance()->Find_Image(L"ESelect2");

	GdiTransparentBlt(
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		this->m_tRect.left + iScrollX - 15.f, // 복사 받을 위치 좌표
		this->m_tRect.top + iScrollY - 15.f,
		64,	// 복사 받을 이미지의 가로, 세로
		64,
		hSelectDC,		// 비트맵을 가지고 있는 DC
		0,			// 비트맵 출력 시작 좌표 LEFT, TOP
		0,
		64,	// 출력할 비트맵 가로
		64,	// 출력할 비트맵 세로
		RGB(0, 0, 0));	// 제거할 색상 값
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
