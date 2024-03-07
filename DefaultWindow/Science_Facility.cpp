#include "stdafx.h"
#include "Science_Facility.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "SoundMgr.h"
CScience_Facility::CScience_Facility()
{
	InsertBmpFile();
}

CScience_Facility::~CScience_Facility()
{
	Release();
}

void CScience_Facility::Initialize()
{
	//처음 크기 고정
	m_tInfo.fCX = 128.f;
	m_tInfo.fCY = 96.f;

	__super::Update_Rect();

	//건물은 애니메이션이 없잖아?
	m_pFrameKey = L"Research";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 1000;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_BUILDING;

	SetObstcale();

	m_Stat.m_Hp = 850.f;
	m_Stat.m_MaxHp = 850.f;

	lstrcpyW(m_Stat.m_Name, L"Science Facility");
}

int CScience_Facility::Update()
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

void CScience_Facility::Late_Update()
{
	CObj_Static::Move_Frame();
}

void CScience_Facility::Render(HDC hDC)
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
			m_tRect.top + iScrollY + (int)m_tInfo.fCY+10.f,
			128,	// 복사 받을 이미지의 가로, 세로
			5,
			hhpDC,		// 비트맵을 가지고 있는 DC
			128 * frame,			// 비트맵 출력 시작 좌표 LEFT, TOP
			5 * m_tFrame.iMotion,
			128,	// 출력할 비트맵 가로
			5,	// 출력할 비트맵 세로
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
		hSelectDC = CBmpMgr::Get_Instance()->Find_Image(L"PSelect8");
	else if (this->Get_FactionState() == FACTION_ENEMY)
		hSelectDC = CBmpMgr::Get_Instance()->Find_Image(L"ESelect8");

	GdiTransparentBlt(
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		this->m_tRect.left + iScrollX - 10.f, // 복사 받을 위치 좌표
		this->m_tRect.top + iScrollY - 20.f,
		148,	// 복사 받을 이미지의 가로, 세로
		148,
		hSelectDC,		// 비트맵을 가지고 있는 DC
		0,			// 비트맵 출력 시작 좌표 LEFT, TOP
		0,
		148,	// 출력할 비트맵 가로
		148,	// 출력할 비트맵 세로
		RGB(0, 0, 0));	// 제거할 색상 값
}

void CScience_Facility::Release()
{
}

void CScience_Facility::Spawn_Unit()
{
}

void CScience_Facility::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Building/Reserch/Research.bmp", L"Research");
}

BUILDINGSTATE CScience_Facility::GetType() const
{
	return STATIC_OBJ_SCIENCE_FACILITY;
}
