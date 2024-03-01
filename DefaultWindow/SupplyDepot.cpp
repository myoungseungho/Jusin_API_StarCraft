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
	//ó�� ũ�� ����
	m_tInfo.fCX = 96.f;
	m_tInfo.fCY = 128.f;

	__super::Update_Rect();

	//�ǹ��� �ִϸ��̼��� ���ݾ�?
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
