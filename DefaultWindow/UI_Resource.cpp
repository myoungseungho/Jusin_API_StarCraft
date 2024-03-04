#include "stdafx.h"
#include "UI_Resource.h"
#include "BmpMgr.h"
#include "EconomyMgr.h"
CUI_Resource::CUI_Resource()
{
}

CUI_Resource::~CUI_Resource()
{
}

void CUI_Resource::Initialize()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CurrentResource.bmp", L"CurrentResource");

    m_eRender = RENDER_UI;
}

int CUI_Resource::Update()
{
    return 0;
}

void CUI_Resource::Late_Update()
{
}

void CUI_Resource::Render(HDC hDC)
{
	HDC	hUIDC = CBmpMgr::Get_Instance()->Find_Image(L"CurrentResource");
	GdiTransparentBlt(
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		550, // 복사 받을 위치 좌표
		10,
		261,	// 복사 받을 이미지의 가로, 세로
		29,
		hUIDC,		// 비트맵을 가지고 있는 DC
		0,			// 비트맵 출력 시작 좌표 LEFT, TOP
		0,
		261,	// 출력할 비트맵 가로
		29,	// 출력할 비트맵 세로
		RGB(0, 0, 0));	// 제거할 색상 값


}

void CUI_Resource::Release()
{
}

UIOBJECTTYPE CUI_Resource::GetType() const
{
    return UIOBJECTTYPE();
}

int CUI_Resource::GetDetailType() const
{
    return 0;
}

void CUI_Resource::InsertBmpFile()
{
}
