#include "stdafx.h"
#include "Mineral.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CMineral::CMineral()
{
	InsertBmpFile();
}

CMineral::~CMineral()
{
	Release();
}

void CMineral::Initialize()
{
	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 96.f;

	m_pFrameKey = L"Mineral";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_BUILDING;
}

int CMineral::Update()
{
	__super::Update_Rect();

	if (!m_IsInfoUpdate)
	{
		CObj_Static::Initialize();
		m_IsInfoUpdate = true;
	}
	return 0;
}

void CMineral::Late_Update()
{
}

void CMineral::Render(HDC hDC)
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

void CMineral::Release()
{
}

void CMineral::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/map/Resource/Mine/Mineral.BMP", L"Mineral");
}
