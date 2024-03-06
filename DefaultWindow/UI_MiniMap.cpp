#include "stdafx.h"
#include "UI_MiniMap.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "Obj_Dynamic.h"
#include "ScrollMgr.h"
#include "Obj_Static.h"
CUI_MiniMap::CUI_MiniMap()
{
}

CUI_MiniMap::~CUI_MiniMap()
{
}

void CUI_MiniMap::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Single/MiniMap.bmp", L"MiniMap");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Single/MiniMapCurrent.bmp", L"MiniMapCurrent");

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

	for (size_t i = 0; i < DYNAMIC_OBJ_END; i++)
	{
		for (auto iter : CObjMgr::Get_Instance()->GetDynamic_Obj_List()[i])
		{
			CObj_Dynamic* dynamicIter = dynamic_cast<CObj_Dynamic*>(iter);

			float unitX = 0.f;
			float unitY = 0.f;

			unitX = dynamicIter->Get_Info().fX;
			unitY = dynamicIter->Get_Info().fY;

			// 유닛의 미니맵 상의 위치 계산
			float miniMapX = (unitX * 161.f) / 4096.f;
			float miniMapY = (unitY * 166.f) / 4096.f;

			int screenX = 8 + static_cast<int>(miniMapX);
			int screenY = 430 + static_cast<int>(miniMapY);

			// 사각형의 크기를 정의합니다.
			int rectSize = 5;

			COLORREF color;

			if (dynamicIter->Get_FactionState() == FACTION_ALLY)
			{
				// 초록색 브러시 생성
				color = RGB(0, 255, 0); // 초록색
			}
			else if (dynamicIter->Get_FactionState() == FACTION_ENEMY)
			{
				// 빨간색 브러시 생성
				color = RGB(255, 0, 0); // 빨간색
			}
			else
				return;

			// 사각형 그리기
			HBRUSH hBrush = CreateSolidBrush(color); // 색상으로 브러시 생성
			HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			// 사각형 그리기 (미니맵 상의 유닛 위치에)
			Rectangle(hDC, screenX, screenY, screenX + rectSize, screenY + rectSize);

			// 정리
			SelectObject(hDC, hOldBrush); // 원래 브러시로 복원
			DeleteObject(hBrush); // 사용한 브러시 삭제
		}
	}

	for (size_t i = 0; i < STATIC_OBJ_MINERAL; i++)
	{
		for (auto iter : CObjMgr::Get_Instance()->GetStatic_Obj_List()[i])
		{
			CObj_Static* staticIter = dynamic_cast<CObj_Static*>(iter);

			float unitX = 0.f;
			float unitY = 0.f;

			unitX = staticIter->Get_Info().fX;
			unitY = staticIter->Get_Info().fY;

			// 유닛의 미니맵 상의 위치 계산
			float miniMapX = (unitX * 161.f) / 4096.f;
			float miniMapY = (unitY * 166.f) / 4096.f;

			int screenX = 8 + static_cast<int>(miniMapX);
			int screenY = 430 + static_cast<int>(miniMapY);

			// 사각형의 크기를 정의합니다.
			int rectSize = 8;

			COLORREF color;

			if (staticIter->Get_FactionState() == FACTION_ALLY)
			{
				// 초록색 브러시 생성
				color = RGB(0, 255, 0); // 초록색
			}
			else if (staticIter->Get_FactionState() == FACTION_ENEMY)
			{
				// 빨간색 브러시 생성
				color = RGB(255, 0, 0); // 빨간색
			}

			// 사각형 그리기
			HBRUSH hBrush = CreateSolidBrush(color); // 색상으로 브러시 생성
			HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			// 사각형 그리기 (미니맵 상의 유닛 위치에)
			Rectangle(hDC, screenX, screenY, screenX + rectSize, screenY + rectSize);

			// 정리
			SelectObject(hDC, hOldBrush); // 원래 브러시로 복원
			DeleteObject(hBrush); // 사용한 브러시 삭제
		}
	}

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hCurrentDC = CBmpMgr::Get_Instance()->Find_Image(L"MiniMapCurrent");
	GdiTransparentBlt(
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		8 + (abs(iScrollX) * 161.f) / 4096.f, // 복사 받을 위치 좌표
		430 + (abs(iScrollY) * 172.f) / 4096.f,
		29,	// 복사 받을 이미지의 가로, 세로
		16,
		hCurrentDC,		// 비트맵을 가지고 있는 DC
		0,			// 비트맵 출력 시작 좌표 LEFT, TOP
		0,
		29,	// 출력할 비트맵 가로
		16,	// 출력할 비트맵 세로
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
