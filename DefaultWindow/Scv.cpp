#include "stdafx.h"
#include "Scv.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Scv_Idle_State.h"
#include "Scv_Walk_State.h"
#include "Scv_Attack_State.h"
#include "Scv_Die_State.h"
#include "Scv_Build_State.h"
#include "Tile.h"
#include "AStarMgr.h"
#include "TileMgr.h"
#include "SpawnMgr.h"
#include "UI_SCV_Display.h"
#include "Scv_Collection_State.h"
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
	if (m_CurrentState == NON_STATE)
	{
		m_eRender = RENDER_GAMEOBJECT;

		//ó�� ũ�� ����
		m_tInfo.fCX = 72.f;
		m_tInfo.fCY = 72.f;

		m_vecState.push_back(new CScv_Idle_State);
		m_vecState.push_back(new CScv_Walk_State);
		m_vecState.push_back(new CScv_Attack_State);
		m_vecState.push_back(new CScv_Die_State);
		m_vecState.push_back(new CScv_Build_State);
		m_vecState.push_back(new CScv_Collection_State);

		ChangeState(IDLE_STATE);

		m_Stat.m_Hp = 60;
		m_Stat.m_Attack = 5;
		m_Stat.m_fSpeed = 3.f;
		m_Stat.m_MaxHp = 60;
		lstrcpyW(m_Stat.m_Name, L"SCV");

		m_tFrameDisplay.iFrameStart = 0;
		m_tFrameDisplay.iFrameEnd = 44;
		m_tFrameDisplay.iMotion = 0;
		m_tFrameDisplay.dwSpeed = 100;
		m_tFrameDisplay.dwTime = GetTickCount();
	}
}

int CScv::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_vecState[m_CurrentState]->Update(this);

	__super::Update_Rect();

	if (m_bCliecked && m_DisPlayCopy == nullptr)
	{
		m_DisPlayCopy = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_SCV_Display>(UI_OBJECT_DISPLAY);
	}
	else if (!m_bCliecked && m_DisPlayCopy != nullptr)
	{
		CObjMgr::Get_Instance()->Delete_ID_UIObj(UI_OBJECT_DISPLAY);
		m_DisPlayCopy = nullptr;
	}

	return OBJ_NOEVENT;
}

void CScv::Late_Update()
{
	m_vecState[m_CurrentState]->Late_Update(this);

	__super::Move_Frame();
}

void CScv::Render(HDC hDC)
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

	if (!m_bCliecked)
		return;

	HDC	hSelectDC = nullptr;
	if (this->Get_FactionState() == FACTION_ALLY)
		hSelectDC = CBmpMgr::Get_Instance()->Find_Image(L"PSelect3");
	else if (this->Get_FactionState() == FACTION_ENEMY)
		hSelectDC = CBmpMgr::Get_Instance()->Find_Image(L"ESelect3");

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

void CScv::Release()
{
	m_vecState[m_CurrentState]->Release(this);
}



void CScv::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Scv/Idle/SCV_UP.bmp", L"SCV_UP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Scv/Idle/SCV_UPRIGHT.bmp", L"SCV_UPRIGHT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Scv/Idle/SCV_RIGHT.bmp", L"SCV_RIGHT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Scv/Idle/SCV_DOWNRIGHT.bmp", L"SCV_DOWNRIGHT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Scv/Idle/SCV_DOWN.bmp", L"SCV_DOWN");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Scv/Idle/SCV_DOWNLEFT.bmp", L"SCV_DOWNLEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Scv/Idle/SCV_LEFT.bmp", L"SCV_LEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Scv/Idle/SCV_UPLEFT.bmp", L"SCV_UPLEFT");

	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_UP] = (L"SCV_UP");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_UP],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RUP] = (L"SCV_UPRIGHT");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RUP],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RIGHT] = (L"SCV_RIGHT");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RIGHT],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RDOWN] = (L"SCV_DOWNRIGHT");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RDOWN],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_DOWN] = (L"SCV_DOWN");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_DOWN],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LDOWN] = (L"SCV_DOWNLEFT");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LDOWN],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LEFT] = (L"SCV_LEFT");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LEFT],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LUP] = (L"SCV_UPLEFT");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LUP],{0,0,0,50,GetTickCount()} });

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Scv/Attack/SCV_UP_Attack.bmp", L"SCV_UP_Attack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Scv/Attack/SCV_UPRIGHT_Attack.bmp", L"SCV_UPRIGHT_Attack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Scv/Attack/SCV_RIGHT_Attack.bmp", L"SCV_RIGHT_Attack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Scv/Attack/SCV_DOWNRIGHT_Attack.bmp", L"SCV_DOWNRIGHT_Attack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Scv/Attack/SCV_DOWN_Attack.bmp", L"SCV_DOWN_Attack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Scv/Attack/SCV_DOWNLEFT_Attack.bmp", L"SCV_DOWNLEFT_Attack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Scv/Attack/SCV_LEFT_Attack.bmp", L"SCV_LEFT_Attack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Scv/Attack/SCV_UPLEFT_Attack.bmp", L"SCV_UPLEFT_Attack");

	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_UP] = (L"SCV_UP_Attack");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_UP],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RUP] = (L"SCV_UPRIGHT_Attack");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RUP],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RIGHT] = (L"SCV_RIGHT_Attack");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RIGHT],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RDOWN] = (L"SCV_DOWNRIGHT_Attack");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RDOWN],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_DOWN] = (L"SCV_DOWN_Attack");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_DOWN],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LDOWN] = (L"SCV_DOWNLEFT_Attack");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LDOWN],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LEFT] = (L"SCV_LEFT_Attack");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LEFT],{0,0,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LUP] = (L"SCV_UPLEFT_Attack");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LUP],{0,0,0,50,GetTickCount()} });

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/ScvAtt/SCV_Bullet.bmp", L"SCV_Bullet");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Bang1/SCV_Die.bmp", L"SCV_Die");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/SCV_Mineral.bmp", L"SCV_Mineral");
}

DYNAMIC_OBJID CScv::GetType() const
{
	return DYNAMIC_OBJ_SCV;
}
