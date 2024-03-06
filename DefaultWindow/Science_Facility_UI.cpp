#include "stdafx.h"
#include "Science_Facility_UI.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
CScience_Facility_UI::CScience_Facility_UI()
{
	InsertBmpFile();
}

CScience_Facility_UI::~CScience_Facility_UI()
{
	Release();
}

void CScience_Facility_UI::Initialize()
{
	//ó�� ũ�� ����
	m_tInfo.fCX = 128.f;
	m_tInfo.fCY = 96.f;

	__super::Update_Rect();

	//�ǹ��� �ִϸ��̼��� ���ݾ�?
	m_pFrameKey = L"Reserach_UI";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_UI;
}

int CScience_Facility_UI::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	UpdateMouse();
	return 0;
}

void CScience_Facility_UI::Late_Update()
{
}

void CScience_Facility_UI::Render(HDC hDC)
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

void CScience_Facility_UI::Release()
{
}

void CScience_Facility_UI::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Building/Reserch/Reserach_UI.bmp", L"Reserach_UI");
}

UIOBJECTTYPE CScience_Facility_UI::GetType() const
{
	return UI_OBJECT_BUILD;
}

int CScience_Facility_UI::GetDetailType() const
{
	return UI_STATIC_OBJ_SCIENCE_FACILITY;
}
