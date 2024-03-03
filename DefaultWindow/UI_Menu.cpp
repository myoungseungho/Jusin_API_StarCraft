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
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		510, // 복사 받을 위치 좌표
		490,
		83,	// 복사 받을 이미지의 가로, 세로
		22,
		hUIDC,		// 비트맵을 가지고 있는 DC
		0,			// 비트맵 출력 시작 좌표 LEFT, TOP
		0,
		83,	// 출력할 비트맵 가로
		22,	// 출력할 비트맵 세로
		RGB(0, 0, 0));	// 제거할 색상 값
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
