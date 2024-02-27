#include "stdafx.h"
#include "Center.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "Obj_Dynamic.h"
#include "SpawnMgr.h"
#include "Scv.h"
CCenter::CCenter()
{
	InsertBmpFile();
}

CCenter::~CCenter()
{
	Release();
}

void CCenter::Initialize()
{
	//ó�� ũ�� ����
	m_tInfo.fCX = 128.f;
	m_tInfo.fCY = 160.f;

	__super::Update_Rect();

	//�ǹ��� �ִϸ��̼��� ���ݾ�?
	m_pFrameKey = L"Center";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_BUILDING;

	SetObstcale();
}

int CCenter::Update()
{
	__super::Update_Rect();

	return 0;
}

void CCenter::Late_Update()
{
}

void CCenter::Render(HDC hDC)
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

void CCenter::Release()
{
}

void CCenter::Spawn_Unit(DYNAMIC_OBJID)
{
	CObj_Dynamic* scv = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CScv>(DYANMIC_OBJ_SCV, FACTION_ALLY, m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY * 0.5f + 10.f);
	m_vecWaitUnit.push_back(scv);
}

void CCenter::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Building/Control/Center.bmp", L"Center");
}

BUILDINGSTATE CCenter::GetType() const
{
	return STATIC_OBJ_CENTER;
}
