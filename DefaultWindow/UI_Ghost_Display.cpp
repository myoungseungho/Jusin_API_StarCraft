#include "stdafx.h"
#include "UI_Ghost_Display.h"
#include "BmpMgr.h"

CUI_Ghost_Display::CUI_Ghost_Display()
{
}

CUI_Ghost_Display::~CUI_Ghost_Display()
{
}

void CUI_Ghost_Display::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Ghost_Display.bmp", L"Ghost_Display");

	m_eRender = RENDER_UI;

	m_pFrameKey = L"Ghost_Display";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 59;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100.f;
	m_tFrame.dwTime = GetTickCount();
}

int CUI_Ghost_Display::Update()
{
	return 0;
}

void CUI_Ghost_Display::Late_Update()
{
	Move_Frame();
}

void CUI_Ghost_Display::Render(HDC hDC)
{
	HDC	hSelectDisplay = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	GdiTransparentBlt(
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		523, // ���� ���� ��ġ ��ǥ
		517,
		60,	// ���� ���� �̹����� ����, ����
		56,
		hSelectDisplay,		// ��Ʈ���� ������ �ִ� DC
		60 * m_tFrame.iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		56 * m_tFrame.iMotion,
		60,	// ����� ��Ʈ�� ����
		56,	// ����� ��Ʈ�� ����
		RGB(0, 0, 0));	// ������ ���� ��
}

void CUI_Ghost_Display::Release()
{
}

UIOBJECTTYPE CUI_Ghost_Display::GetType() const
{
	return UI_OBJECT_DISPLAY;
}

int CUI_Ghost_Display::GetDetailType() const
{
	return 0;
}
