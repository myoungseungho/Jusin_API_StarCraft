#include "stdafx.h"
#include "Academy_UI.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
CAcademy_UI::CAcademy_UI()
{
    InsertBmpFile();
}

CAcademy_UI::~CAcademy_UI()
{
    Release();
}

void CAcademy_UI::Initialize()
{
	//ó�� ũ�� ����
	m_tInfo.fCX = 96.f;
	m_tInfo.fCY = 128.f;

	__super::Update_Rect();

	//�ǹ��� �ִϸ��̼��� ���ݾ�?
	m_pFrameKey = L"Academy_UI";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_UI;
}

int CAcademy_UI::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	UpdateMouse();
	return 0;
}

void CAcademy_UI::Late_Update()
{
}

void CAcademy_UI::Render(HDC hDC)
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

void CAcademy_UI::Release()
{
}

void CAcademy_UI::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Building/Academy/Academy_UI.bmp", L"Academy_UI");
}

UIOBJECTTYPE CAcademy_UI::GetType() const
{
	return UI_OBJECT_BUILD;
}

int CAcademy_UI::GetDetailType() const
{
	return UI_STATIC_OBJ_ACADEMY;
}