#include "stdafx.h"
#include "Nuclear.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SpawnMgr.h"
#include "Nuclear_Effect.h"
#include "ObjMgr.h"
CNuclear::CNuclear() :m_fInitY(0.f)
{
	InsertBmpFile();
}

CNuclear::~CNuclear()
{
	Release();
}

void CNuclear::Initialize()
{
	m_eRender = RENDER_UI;
	m_Collision = COLLISION_NOT;
	//처음 크기 고정
	m_tInfo.fCX = 48.f;
	m_tInfo.fCY = 40.f;
	m_fInitY = m_tInfo.fY;
	m_tInfo.fY -= 300.f;
	__super::Update_Rect();

	m_Stat.m_Hp = 45;
	m_Stat.m_Attack = 500;
	m_Stat.m_AttackRange = 400.f;
	m_Stat.m_DetectionRange = 400.f;
	m_Stat.m_fSpeed = 3.f;
	m_Stat.m_MaxHp = 45;
	lstrcpyW(m_Stat.m_Name, L"Nuclear");

	m_pFrameKey = L"Nuclear";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();
}

int CNuclear::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Set_PosY(m_Stat.m_fSpeed);
	__super::Update_Rect();

	if (CheckDestination())
	{
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			list <CObj*> nearObjList = CObjMgr::Get_Instance()->GetNearUnit(this, 300.f);
			for (auto iter : nearObjList)
			{
				dynamic_cast<CObj_Dynamic*>(iter)->Set_Damage(m_Stat.m_Attack);
			}
			CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CNuclear_Effect>(DYNAMIC_OBJ_NUCLEAR_EFFECT, FACTION_NON, m_tInfo.fX, m_tInfo.fY);
			m_bDead = true;
		}
	}

	return 0;
}

void CNuclear::Late_Update()
{
	Move_Frame();
}

void CNuclear::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

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
}

void CNuclear::Release()
{
}


void CNuclear::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/NukeMissile/Nuclear.bmp", L"Nuclear");
}

bool CNuclear::CheckDestination()
{
	if (m_tInfo.fY > m_fInitY)
		return true;
	else
		return false;
}



DYNAMIC_OBJID CNuclear::GetType() const
{
	return DYNAMIC_OBJ_NUCLEAR;
}

