#include "stdafx.h"
#include "Barrack.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "Obj_Dynamic.h"
#include "SpawnMgr.h"
#include "Marine.h"
#include "FireBat.h"
#include "Medic.h"
CBarrack::CBarrack()
{
	InsertBmpFile();
}

CBarrack::~CBarrack()
{
	Release();
}

void CBarrack::Initialize()
{
	//처음 크기 고정
	m_tInfo.fCX = 192.f;
	m_tInfo.fCY = 160.f;

	__super::Update_Rect();

	//건물은 애니메이션이 없잖아?
	m_pFrameKey = L"Barrack";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_BUILDING;

	m_Stat.m_MaxHp = 1000.f;
	m_Stat.m_Hp = 1000.f;
	SetObstcale();

	lstrcpyW(m_Stat.m_Name, L"Barrack");
}

int CBarrack::Update()
{
	__super::Update_Rect();

	if (!m_UIBuilding)
	{
		bool bCanBuild = CTileMgr::Get_Instance()->CanAddBuild(this);
	}
	else if (m_UIBuilding)
		UIBuilding();

	return 0;
}

void CBarrack::Late_Update()
{
}

void CBarrack::Render(HDC hDC)
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

	if (!m_bCliecked)
		return;

	HDC	hSelectDC = nullptr;
	if (this->Get_FactionState() == FACTION_ALLY)
		hSelectDC = CBmpMgr::Get_Instance()->Find_Image(L"PSelect8");
	else if (this->Get_FactionState() == FACTION_ENEMY)
		hSelectDC = CBmpMgr::Get_Instance()->Find_Image(L"ESelect8");

	GdiTransparentBlt(
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		this->m_tRect.left + iScrollX + 25.f, // 복사 받을 위치 좌표
		this->m_tRect.top + iScrollY + 10.f,
		148,	// 복사 받을 이미지의 가로, 세로
		148,
		hSelectDC,		// 비트맵을 가지고 있는 DC
		0,			// 비트맵 출력 시작 좌표 LEFT, TOP
		0,
		148,	// 출력할 비트맵 가로
		148,	// 출력할 비트맵 세로
		RGB(0, 0, 0));	// 제거할 색상 값
}

void CBarrack::Release()
{
}

void CBarrack::Spawn_Unit(DYNAMIC_OBJID _objId)
{
	CObj_Dynamic* obj = nullptr;
	if (_objId == DYNAMIC_OBJ_MARINE)
	{
		obj = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMarine>(DYNAMIC_OBJ_MARINE, FACTION_ALLY, m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY * 0.5f + 10.f);
	}
	else if (_objId == DYNAMIC_OBJ_FIREBAT)
	{
		obj = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CFireBat>(DYNAMIC_OBJ_FIREBAT, FACTION_ALLY, m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY * 0.5f + 10.f);
	}
	else if (_objId == DYNAMIC_OBJ_MEDIC)
	{
		obj = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMedic>(DYNAMIC_OBJ_MEDIC, FACTION_ALLY, m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY * 0.5f + 10.f);
	}

	m_vecWaitUnit.push_back(obj);
}

void CBarrack::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Building/Barrack/Barrack.bmp", L"Barrack");
}

BUILDINGSTATE CBarrack::GetType() const
{
	return STATIC_OBJ_BARRACK;
}
