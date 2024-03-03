#include "stdafx.h"
#include "UI_Menu.h"
#include "BmpMgr.h"
CUI_Menu::CUI_Menu()
{
}

CUI_Menu::~CUI_Menu()
{
}

void CUI_Menu::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/MenuButton/Menu.bmp", L"Menu");

	m_eRender = RENDER_UI;
}

int CUI_Menu::Update()
{
	return 0;
}

void CUI_Menu::Late_Update()
{
}

void CUI_Menu::Render(HDC hDC)
{
	HDC	hUIDC = CBmpMgr::Get_Instance()->Find_Image(L"Menu");
	GdiTransparentBlt(
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		510, // ���� ���� ��ġ ��ǥ
		490,
		83,	// ���� ���� �̹����� ����, ����
		22,
		hUIDC,		// ��Ʈ���� ������ �ִ� DC
		0,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		0,
		83,	// ����� ��Ʈ�� ����
		22,	// ����� ��Ʈ�� ����
		RGB(0, 0, 0));	// ������ ���� ��
}

void CUI_Menu::Release()
{
}

UIOBJECTTYPE CUI_Menu::GetType() const
{
	return UIOBJECTTYPE();
}

int CUI_Menu::GetDetailType() const
{
	return 0;
}
