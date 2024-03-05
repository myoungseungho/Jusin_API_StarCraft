#include "stdafx.h"
#include "Ghost.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Ghost_Idle_State.h"
#include "Ghost_Walk_State.h"
#include "Ghost_Attack_State.h"
#include "Ghost_Die_State.h"
#include "SpawnMgr.h"
#include "UI_Ghost_Display.h"
CGhost::CGhost()
{
	InsertBmpFile();
}

CGhost::~CGhost()
{
	Release();
}

void CGhost::Initialize()
{
	if (m_CurrentState == NON_STATE)
	{
		m_eRender = RENDER_GAMEOBJECT;

		//ó�� ũ�� ����
		m_tInfo.fCX = 64.f;
		m_tInfo.fCY = 64.f;

		m_vecState.push_back(new CGhost_Idle_State);
		m_vecState.push_back(new CGhost_Walk_State);
		m_vecState.push_back(new CGhost_Attack_State);
		m_vecState.push_back(new CGhost_Die_State);

		ChangeState(IDLE_STATE);

		m_Stat.m_Hp = 45;
		m_Stat.m_Attack = 1;
		m_Stat.m_AttackRange = 130.f;
		m_Stat.m_DetectionRange = 200.f;
		m_Stat.m_fSpeed = 3.f;
		m_Stat.m_MaxHp = 45;
		lstrcpyW(m_Stat.m_Name, L"Ghost");
	}
}

int CGhost::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();
	m_vecState[m_CurrentState]->Update(this);

	if (m_bCliecked && m_DisPlayCopy == nullptr)
	{
		m_DisPlayCopy = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Ghost_Display>(UI_OBJECT_DISPLAY);
	}
	else if (!m_bCliecked && m_DisPlayCopy != nullptr)
	{
		CObjMgr::Get_Instance()->Delete_ID_UIObj(UI_OBJECT_DISPLAY);
		m_DisPlayCopy = nullptr;
	}

	return 0;
}

void CGhost::Late_Update()
{
	m_vecState[m_CurrentState]->Late_Update(this);

	__super::Move_Frame();
}

void CGhost::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	int grade = m_Stat.m_MaxHp / 6;
	int currentGrade = m_Stat.m_Hp / grade;
	int frame = currentGrade == 0 ? 5 : currentGrade == 1 ? 5 : currentGrade == 2 ? 4 : currentGrade == 3 ? 3
		: currentGrade == 4 ? 2 : currentGrade == 5 ? 1 : currentGrade == 6 ? 0 : 0;

	HDC	hhpDC = CBmpMgr::Get_Instance()->Find_Image(L"Small_Hp");

	GdiTransparentBlt(
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		m_tRect.left + iScrollX + 20.f, // ���� ���� ��ġ ��ǥ
		m_tRect.top + iScrollY + (int)m_tInfo.fCY - 15.f,
		32,	// ���� ���� �̹����� ����, ����
		5,
		hhpDC,		// ��Ʈ���� ������ �ִ� DC
		32 * frame,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		5 * m_tFrame.iMotion,
		32,	// ����� ��Ʈ�� ����
		5,	// ����� ��Ʈ�� ����
		RGB(0, 0, 0));	// ������ ���� ��

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

	if (!m_bCliecked)
		return;

	HDC	hSelectDC = nullptr;
	if (this->Get_FactionState() == FACTION_ALLY)
		hSelectDC = CBmpMgr::Get_Instance()->Find_Image(L"PSelect2");
	else if (this->Get_FactionState() == FACTION_ENEMY)
		hSelectDC = CBmpMgr::Get_Instance()->Find_Image(L"ESelect2");

	GdiTransparentBlt(
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		this->m_tRect.left + iScrollX, // ���� ���� ��ġ ��ǥ
		this->m_tRect.top + iScrollY,
		64,	// ���� ���� �̹����� ����, ����
		64,
		hSelectDC,		// ��Ʈ���� ������ �ִ� DC
		0,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		0,
		64,	// ����� ��Ʈ�� ����
		64,	// ����� ��Ʈ�� ����
		RGB(0, 0, 0));	// ������ ���� ��
}

void CGhost::Release()
{
}

DYNAMIC_OBJID CGhost::GetType() const
{
	return DYNAMIC_OBJ_GHOST;
}

void CGhost::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Ghost/Idle/Ghost_Idle.bmp", L"Ghost_Idle");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Ghost/Work/Ghost_Walk_Up.bmp", L"Ghost_Walk_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Ghost/Work/Ghost_Walk_Up_Right.bmp", L"Ghost_Walk_Up_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Ghost/Work/Ghost_Walk_Right.bmp", L"Ghost_Walk_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Ghost/Work/Ghost_Walk_Down_Right.bmp", L"Ghost_Walk_Down_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Ghost/Work/Ghost_Walk_Down.bmp", L"Ghost_Walk_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Ghost/Work/Ghost_Walk_Down_Left.bmp", L"Ghost_Walk_Down_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Ghost/Work/Ghost_Walk_Left.bmp", L"Ghost_Walk_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Ghost/Work/Ghost_Walk_Up_Left.bmp", L"Ghost_Walk_Up_Left");

	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_UP] = (L"Ghost_Walk_Up");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_UP],{0,18,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RUP] = (L"Ghost_Walk_Up_Right");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RUP],{0,17,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RIGHT] = (L"Ghost_Walk_Right");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RIGHT],{0,17,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RDOWN] = (L"Ghost_Walk_Down_Right");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RDOWN],{0,17,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_DOWN] = (L"Ghost_Walk_Down");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_DOWN],{0,8,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LDOWN] = (L"Ghost_Walk_Down_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LDOWN],{0,17,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LEFT] = (L"Ghost_Walk_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LEFT],{0,17,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LUP] = (L"Ghost_Walk_Up_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LUP],{0,17,0,50,GetTickCount()} });

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Ghost/Attack/Ghost_Attack_Up.bmp", L"Ghost_Attack_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Ghost/Attack/Ghost_Attack_Up_Right.bmp", L"Ghost_Attack_Up_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Ghost/Attack/Ghost_Attack_Right.bmp", L"Ghost_Attack_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Ghost/Attack/Ghost_Attack_Down_Right.bmp", L"Ghost_Attack_Down_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Ghost/Attack/Ghost_Attack_Down.bmp", L"Ghost_Attack_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Ghost/Attack/Ghost_Attack_Down_Left.bmp", L"Ghost_Attack_Down_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Ghost/Attack/Ghost_Attack_Left.bmp", L"Ghost_Attack_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Ghost/Attack/Ghost_Attack_Up_Left.bmp", L"Ghost_Attack_Up_Left");

	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_UP] = (L"Ghost_Attack_Up");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_UP],{0,0,0,100,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RUP] = (L"Ghost_Attack_Up_Right");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RUP],{0,0,0,100,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RIGHT] = (L"Ghost_Attack_Right");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RIGHT],{0,0,0,100,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RDOWN] = (L"Ghost_Attack_Down_Right");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RDOWN],{0,0,0,100,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_DOWN] = (L"Ghost_Attack_Down");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_DOWN],{0,0,0,100,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LDOWN] = (L"Ghost_Attack_Down_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LDOWN],{0,0,0,100,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LEFT] = (L"Ghost_Attack_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LEFT],{0,0,0,100,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LUP] = (L"Ghost_Attack_Up_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LUP],{0,0,0,100,GetTickCount()} });

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Ghost/Die/Ghost_Die.bmp", L"Ghost_Die");
}
