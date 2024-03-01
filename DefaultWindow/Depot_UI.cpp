#include "stdafx.h"
#include "Depot_UI.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CDepot_UI::CDepot_UI()
{
    InsertBmpFile();
}

CDepot_UI::~CDepot_UI()
{
    Release();
}

void CDepot_UI::Initialize()
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

	m_eRender = RENDER_UI;
}

int CDepot_UI::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	UpdateMouse();
	return 0;
}

void CDepot_UI::Late_Update()
{
}

void CDepot_UI::Render(HDC hDC)
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

void CDepot_UI::Release()
{
}



void CDepot_UI::InsertBmpFile()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Building/Depot/Depot.bmp", L"Depot");
}

UIOBJECTTYPE CDepot_UI::GetType() const
{
	return UI_OBJECT_BUILD;
}

int CDepot_UI::GetDetailType() const
{
	return UI_STATIC_OBJ_DEPOT;
}
