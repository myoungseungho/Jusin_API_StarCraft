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

		ChangeState(IDLE_STATE);

		m_Stat.m_Hp = 60.f;
		m_Stat.m_Attack = 5.f;
	}
}

int CScv::Update()
{
	if (m_bDead)
		OBJ_DEAD;

	if (m_Collision == COLLISION_OK)
		m_Collision = COLLISION_END;

	m_vecState[m_CurrentState]->Update(this);

	__super::Update_Rect();

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
}

void CScv::Release()
{
	m_vecState[m_CurrentState]->Release(this);
}



void CScv::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Scv/Idle/SCV_IDLE.bmp", L"SCV_IDLE");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Scv/Attack/SCV_ATTACK.bmp", L"SCV_ATTACK");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/ScvAtt/SCV_Bullet.bmp", L"SCV_Bullet");
}

DYNAMIC_OBJID CScv::GetType() const
{
	return DYANMIC_OBJ_SCV;
}
