#include "stdafx.h"
#include "UI_MiniMap.h"
#include "BmpMgr.h"
CUI_MiniMap::CUI_MiniMap()
{
}

CUI_MiniMap::~CUI_MiniMap()
{
}

void CUI_MiniMap::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Single/MiniMap.bmp", L"MiniMap");

	m_eRender = RENDER_UI;
}

int CUI_MiniMap::Update()
{
	return 0;
}

void CUI_MiniMap::Late_Update()
{
}

void CUI_MiniMap::Render(HDC hDC)
{
	HDC	hUIDC = CBmpMgr::Get_Instance()->Find_Image(L"MiniMap");
	GdiTransparentBlt(
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		8, // 복사 받을 위치 좌표
		430,
		161,	// 복사 받을 이미지의 가로, 세로
		166,
		hUIDC,		// 비트맵을 가지고 있는 DC
		0,			// 비트맵 출력 시작 좌표 LEFT, TOP
		0,
		161,	// 출력할 비트맵 가로
		166,	// 출력할 비트맵 세로
		RGB(0, 0, 0));	// 제거할 색상 값
}

void CUI_MiniMap::Release()
{
}

UIOBJECTTYPE CUI_MiniMap::GetType() const
{
	return UIOBJECTTYPE();
}

int CUI_MiniMap::GetDetailType() const
{
	return 0;
}
