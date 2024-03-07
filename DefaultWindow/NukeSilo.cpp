#include "stdafx.h"
#include "NukeSilo.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
CNukeSilo::CNukeSilo() : m_CompleteAddon(false)
{
	InsertBmpFile();
}

CNukeSilo::~CNukeSilo()
{
	Release();
}

void CNukeSilo::Initialize()
{
	//처음 크기 고정
	m_tInfo.fCX = 128.f;
	m_tInfo.fCY = 64.f;

	__super::Update_Rect();

	//건물은 애니메이션이 없잖아?
	m_pFrameKey = L"Nukesilo";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 1000;
	m_tFrame.dwTime = GetTickCount();

	m_pFrameConnectKey = L"Nukesilo_Connection";
	m_tFrameConnect.iFrameStart = 0;
	m_tFrameConnect.iFrameEnd = 4;
	m_tFrameConnect.iMotion = 0;
	m_tFrameConnect.dwSpeed = 50;
	m_tFrameConnect.dwTime = GetTickCount();

	m_eRender = RENDER_BUILDING;

	SetObstcale();

	m_Stat.m_Hp = 600.f;
	m_Stat.m_MaxHp = 600.f;

	lstrcpyW(m_Stat.m_Name, L"Nuclear silo");
}

int CNukeSilo::Update()
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

void CNukeSilo::Late_Update()
{
	CObj_Static::Move_Frame();

	if (m_CompleteBuilding)
	{
		if (m_CompleteAddon)
			return;

		if (m_tFrameConnect.dwTime + m_tFrameConnect.dwSpeed < GetTickCount())
		{
			++m_tFrameConnect.iFrameStart;

			if (m_tFrameConnect.iFrameStart > m_tFrameConnect.iFrameEnd)
			{
				m_tFrameConnect.iFrameStart = m_tFrameConnect.iFrameEnd;
				m_CompleteAddon = true;
			}

			m_tFrameConnect.dwTime = GetTickCount();
		}
	}
}

void CNukeSilo::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_CompleteBuilding)
	{
		int grade = m_Stat.m_MaxHp / 6;
		int currentGrade = m_Stat.m_Hp / grade;
		int frame = currentGrade == 0 ? 5 : currentGrade == 1 ? 5 : currentGrade == 2 ? 4 : currentGrade == 3 ? 3
			: currentGrade == 4 ? 2 : currentGrade == 5 ? 1 : currentGrade == 6 ? 0 : 0;

		HDC	hhpDC = CBmpMgr::Get_Instance()->Find_Image(L"Big_Hp");

		GdiTransparentBlt(
			hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
			m_tRect.left + iScrollX, // 복사 받을 위치 좌표
			m_tRect.top + iScrollY + (int)m_tInfo.fCY,
			128,	// 복사 받을 이미지의 가로, 세로
			5,
			hhpDC,		// 비트맵을 가지고 있는 DC
			128 * frame,			// 비트맵 출력 시작 좌표 LEFT, TOP
			5 * m_tFrame.iMotion,
			128,	// 출력할 비트맵 가로
			5,	// 출력할 비트맵 세로
			RGB(0, 0, 0));	// 제거할 색상 값

		HDC	hConnect = CBmpMgr::Get_Instance()->Find_Image(m_pFrameConnectKey);

		GdiTransparentBlt(
			hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
			m_tRect.left + iScrollX, // 복사 받을 위치 좌표
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,	// 복사 받을 이미지의 가로, 세로
			(int)m_tInfo.fCY,
			hConnect,		// 비트맵을 가지고 있는 DC
			(int)m_tInfo.fCX * m_tFrameConnect.iFrameStart,			// 비트맵 출력 시작 좌표 LEFT, TOP
			(int)m_tInfo.fCY * m_tFrameConnect.iMotion,
			(int)m_tInfo.fCX,	// 출력할 비트맵 가로
			(int)m_tInfo.fCY,	// 출력할 비트맵 세로
			RGB(0, 0, 0));	// 제거할 색상 값
	}

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
		hSelectDC = CBmpMgr::Get_Instance()->Find_Image(L"PSelect7");
	else if (this->Get_FactionState() == FACTION_ENEMY)
		hSelectDC = CBmpMgr::Get_Instance()->Find_Image(L"ESelect7");

	GdiTransparentBlt(
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		this->m_tRect.left + iScrollX, // 복사 받을 위치 좌표
		this->m_tRect.top + iScrollY -20.f,
		128,	// 복사 받을 이미지의 가로, 세로
		128,
		hSelectDC,		// 비트맵을 가지고 있는 DC
		0,			// 비트맵 출력 시작 좌표 LEFT, TOP
		0,
		128,	// 출력할 비트맵 가로
		128,	// 출력할 비트맵 세로
		RGB(0, 0, 0));	// 제거할 색상 값
}

void CNukeSilo::Release()
{
}

void CNukeSilo::Spawn_Unit(DYNAMIC_OBJID)
{
}

void CNukeSilo::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Building/Nukelsilo/Nukesilo.bmp", L"Nukesilo");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Building/Nukelsilo/Nukesilo_Connection.bmp", L"Nukesilo_Connection");
}

BUILDINGSTATE CNukeSilo::GetType() const
{
	return STATIC_OBJ_NUCLEARSILO;
}
