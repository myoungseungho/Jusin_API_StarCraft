#include "stdafx.h"
#include "SupplyDepot.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "TileMgr.h"
CSupplyDepot::CSupplyDepot()
{
	InsertBmpFile();
}

CSupplyDepot::~CSupplyDepot()
{
	Release();
}

void CSupplyDepot::Initialize()
{
	//처음 크기 고정
	m_tInfo.fCX = 96.f;
	m_tInfo.fCY = 128.f;

	__super::Update_Rect();

	//건물은 애니메이션이 없잖아?
	m_pFrameKey = L"Depot";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_BUILDING;

	SetObstcale();

	m_Stat.m_MaxHp = 500.f;
	m_Stat.m_Hp = 500.f;
	lstrcpyW(m_Stat.m_Name, L"Supply Depot");
}

int CSupplyDepot::Update()
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

void CSupplyDepot::Late_Update()
{
}

void CSupplyDepot::Render(HDC hDC)
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

void CSupplyDepot::Release()
{
}

void CSupplyDepot::Spawn_Unit()
{
}

void CSupplyDepot::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Building/Depot/Depot.bmp", L"Depot");
}

BUILDINGSTATE CSupplyDepot::GetType() const
{
	return STATIC_OBJ_DEPOT;
}
