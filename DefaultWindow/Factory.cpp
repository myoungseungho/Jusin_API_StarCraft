#include "stdafx.h"
#include "Factory.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
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
	//ó�� ũ�� ����
	m_tInfo.fCX = 128.f;
	m_tInfo.fCY = 160.f;

	//�ǹ��� �ִϸ��̼��� ���ݾ�?
	m_pFrameKey = L"Factory";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_BUILDING;
}

int CFactory::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	if (!m_IsInfoUpdate)
	{
		SetObstcale();
		m_IsInfoUpdate = true;
	}

	return 0;
}

void CFactory::Late_Update()
{
}

void CFactory::Render(HDC hDC)
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

void CFactory::Release()
{
}

void CFactory::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Building/Factory/Factory.bmp", L"Factory");
}

BUILDINGSTATE CFactory::GetType() const
{
	return STATIC_OBJ_FACTORY;
}
