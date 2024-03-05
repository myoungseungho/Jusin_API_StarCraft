#include "stdafx.h"
#include "Factory.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "Obj_Dynamic.h"
#include "SpawnMgr.h"
#include "Tank.h"
CFactory::CFactory()
{
	InsertBmpFile();
}

CFactory::~CFactory()
{
	Release();
}

void CFactory::Initialize()
{
	//처음 크기 고정
	m_tInfo.fCX = 128.f;
	m_tInfo.fCY = 160.f;

	__super::Update_Rect();

	//건물은 애니메이션이 없잖아?
	m_pFrameKey = L"Factory";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 1000;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_BUILDING;

	SetObstcale();

	m_Stat.m_Hp = 1500.f;
	m_Stat.m_MaxHp = 1500.f;

	lstrcpyW(m_Stat.m_Name, L"Factory");
}

int CFactory::Update()
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

void CFactory::Late_Update()
{
	CObj_Static::Move_Frame();
}

void CFactory::Render(HDC hDC)
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
		this->m_tRect.left + iScrollX - 10.f, // 복사 받을 위치 좌표
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

void CFactory::Release()
{
}

void CFactory::Spawn_Unit(DYNAMIC_OBJID _objId)
{
	CObj_Dynamic* obj = nullptr;
	if (_objId == DYNAMIC_OBJ_TANK)
	{
		obj = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CTank>(DYNAMIC_OBJ_TANK, FACTION_ALLY, m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY * 0.5f + 10.f);
	}

	m_vecWaitUnit.push_back(obj);
}


void CFactory::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Building/Factory/Factory.bmp", L"Factory");
}

BUILDINGSTATE CFactory::GetType() const
{
	return STATIC_OBJ_FACTORY;
}
