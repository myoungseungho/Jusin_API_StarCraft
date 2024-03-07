#include "stdafx.h"
#include "MyMenu.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
CMyMenu::CMyMenu() :m_bSingleOn(false), m_bEditorOn(false), m_bExitOn(false), m_InitLogoOn(false), m_CurrentTime(GetTickCount())
{
}


CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize()
{
	m_CurrentTime = GetTickCount();
	CSoundMgr::Get_Instance()->InitializeLogo();
	m_InitLogoOn = true;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Single/MainLogo.bmp", L"MainLogo");

	m_Mouse.Initialize();
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Single/MenuBlack.bmp", L"MenuBlack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/MainMenu/Editor/Editor_84.bmp", L"Editor_84");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/MainMenu/Exit/Exit_49.bmp", L"Exit_49");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/MainMenu/SinglePlay/SinglePlay.bmp", L"SinglePlay");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/MainMenu/Button/Single/Single_Button.bmp", L"Single_Button");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/MainMenu/Button/editor/Editor_Button.bmp", L"Editor_Button");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/MainMenu/Button/Exit/Exit_Button.bmp", L"Exit_Button");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/MainMenu/SMouseOn/SMouseOn.bmp", L"SMouseOn");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/MainMenu/XMouseOn/XMouseOn.bmp", L"XMouseOn");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/MainMenu/EMouseOn/EMouseOn.bmp", L"EMouseOn");


	m_pSingleFrameKey = L"SinglePlay";
	m_tSingleFrame.iFrameStart = 0;
	m_tSingleFrame.iFrameEnd = 34;
	m_tSingleFrame.iMotion = 0;
	m_tSingleFrame.dwSpeed = 50;
	m_tSingleFrame.dwTime = GetTickCount();

	m_pSingleOnFrameKey = L"SMouseOn";
	m_tSingleOnFrame.iFrameStart = 0;
	m_tSingleOnFrame.iFrameEnd = 59;
	m_tSingleOnFrame.iMotion = 0;
	m_tSingleOnFrame.dwSpeed = 50;
	m_tSingleOnFrame.dwTime = GetTickCount();

	m_pEditorFrameKey = L"Editor_84";
	m_tEditorFrame.iFrameStart = 0;
	m_tEditorFrame.iFrameEnd = 84;
	m_tEditorFrame.iMotion = 0;
	m_tEditorFrame.dwSpeed = 50;
	m_tEditorFrame.dwTime = GetTickCount();

	m_pEditorOnFrameKey = L"EMouseOn";
	m_tEditorOnFrame.iFrameStart = 0;
	m_tEditorOnFrame.iFrameEnd = 19;
	m_tEditorOnFrame.iMotion = 0;
	m_tEditorOnFrame.dwSpeed = 50;
	m_tEditorOnFrame.dwTime = GetTickCount();

	m_pExitFrameKey = L"Exit_49";
	m_tExitFrame.iFrameStart = 0;
	m_tExitFrame.iFrameEnd = 49;
	m_tExitFrame.iMotion = 0;
	m_tExitFrame.dwSpeed = 50;
	m_tExitFrame.dwTime = GetTickCount();

	m_pExitOnFrameKey = L"XMouseOn";
	m_tExitOnFrame.iFrameStart = 0;
	m_tExitOnFrame.iFrameEnd = 29;
	m_tExitOnFrame.iMotion = 0;
	m_tExitOnFrame.dwSpeed = 50;
	m_tExitOnFrame.dwTime = GetTickCount();

	m_pSingleTextFrameKey = L"Single_Button";
	m_tSingleTextFrame.iFrameStart = 0;
	m_tSingleTextFrame.iFrameEnd = 1;
	m_tSingleTextFrame.iMotion = 0;
	m_tSingleTextFrame.dwSpeed = 50;
	m_tSingleTextFrame.dwTime = GetTickCount();

	m_pEditorTextFrameKey = L"Editor_Button";
	m_tEditorTextFrame.iFrameStart = 0;
	m_tEditorTextFrame.iFrameEnd = 1;
	m_tEditorTextFrame.iMotion = 0;
	m_tEditorTextFrame.dwSpeed = 50;
	m_tEditorTextFrame.dwTime = GetTickCount();

	m_pExitTextFrameKey = L"Exit_Button";
	m_tExitTextFrame.iFrameStart = 0;
	m_tExitTextFrame.iFrameEnd = 1;
	m_tExitTextFrame.iMotion = 0;
	m_tExitTextFrame.dwSpeed = 50;
	m_tExitTextFrame.dwTime = GetTickCount();
}

int CMyMenu::Update()
{
	if (m_InitLogoOn)
	{
		float currentTime = GetTickCount();
		m_CurrentTime++;

		if (m_CurrentTime + 3000.f < currentTime)
			m_InitLogoOn = false;
	}
	else
	{
		m_Mouse.Update();
		float mouseX = m_Mouse.Get_Info().fX;
		float mouseY = m_Mouse.Get_Info().fY;

		//싱글플레이 호버링
		if (mouseX >= 50.f && mouseX <= 370.f && mouseY >= 100.f && mouseY <= 216.f)
		{
			m_bSingleOn = true;
			m_bEditorOn = false;
			m_bExitOn = false;

			if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
			{
				CSoundMgr::Get_Instance()->StopAll();
				CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE);
			}
		}
		//에디터 호버링
		else if (mouseX >= 500 && mouseX <= 660.f && mouseY >= 150.f && mouseY <= 290.f)
		{
			m_bSingleOn = false;
			m_bEditorOn = true;
			m_bExitOn = false;
		}
		//엑시트 호버링
		else if (mouseX >= 500.f && mouseX <= 684.f && mouseY >= 400.f && mouseY <= 528.f)
		{
			m_bSingleOn = false;
			m_bEditorOn = false;
			m_bExitOn = true;
		}
		else
		{
			m_bSingleOn = false;
			m_bEditorOn = false;
			m_bExitOn = false;
		}
	}

	return 0;
}

void CMyMenu::Late_Update()
{
	m_Mouse.Late_Update();

	if (m_InitLogoOn)
		return;

	if (m_tSingleFrame.dwTime + m_tSingleFrame.dwSpeed < GetTickCount())
	{
		++m_tSingleFrame.iFrameStart;

		if (m_tSingleFrame.iFrameStart > m_tSingleFrame.iFrameEnd)
		{
			m_tSingleFrame.iFrameStart = 0;
		}

		m_tSingleFrame.dwTime = GetTickCount();
	}

	if (m_bSingleOn)
	{
		if (m_tSingleOnFrame.dwTime + m_tSingleOnFrame.dwSpeed < GetTickCount())
		{
			++m_tSingleOnFrame.iFrameStart;

			if (m_tSingleOnFrame.iFrameStart > m_tSingleOnFrame.iFrameEnd)
			{
				m_tSingleOnFrame.iFrameStart = 0;
			}

			m_tSingleOnFrame.dwTime = GetTickCount();
		}

		m_tSingleTextFrame.iFrameStart = 1;
	}
	else
	{
		m_tSingleTextFrame.iFrameStart = 0;
	}


	if (m_tEditorFrame.dwTime + m_tEditorFrame.dwSpeed < GetTickCount())
	{
		++m_tEditorFrame.iFrameStart;

		if (m_tEditorFrame.iFrameStart > m_tEditorFrame.iFrameEnd)
		{
			m_tEditorFrame.iFrameStart = 0;
		}

		m_tEditorFrame.dwTime = GetTickCount();
	}

	if (m_bEditorOn)
	{
		if (m_tEditorOnFrame.dwTime + m_tEditorOnFrame.dwSpeed < GetTickCount())
		{
			++m_tEditorOnFrame.iFrameStart;

			if (m_tEditorOnFrame.iFrameStart > m_tEditorOnFrame.iFrameEnd)
			{
				m_tEditorOnFrame.iFrameStart = 0;
			}

			m_tEditorOnFrame.dwTime = GetTickCount();
		}
		m_tEditorTextFrame.iFrameStart = 1;
	}
	else
	{
		m_tEditorTextFrame.iFrameStart = 0;
	}


	if (m_tExitFrame.dwTime + m_tExitFrame.dwSpeed < GetTickCount())
	{
		++m_tExitFrame.iFrameStart;

		if (m_tExitFrame.iFrameStart > m_tExitFrame.iFrameEnd)
		{
			m_tExitFrame.iFrameStart = 0;
		}

		m_tExitFrame.dwTime = GetTickCount();
	}

	if (m_bExitOn)
	{
		if (m_tExitOnFrame.dwTime + m_tExitOnFrame.dwSpeed < GetTickCount())
		{
			++m_tExitOnFrame.iFrameStart;

			if (m_tExitOnFrame.iFrameStart > m_tExitOnFrame.iFrameEnd)
			{
				m_tExitOnFrame.iFrameStart = 0;
			}

			m_tExitOnFrame.dwTime = GetTickCount();
		}
		m_tExitTextFrame.iFrameStart = 1;
	}
	else
	{
		m_tExitTextFrame.iFrameStart = 0;
	}
}

void CMyMenu::Render(HDC hDC)
{
	if (m_InitLogoOn)
	{
		HDC	hLogoMemDC = CBmpMgr::Get_Instance()->Find_Image(L"MainLogo");

		BitBlt(hDC,
			0, 0, WINCX, WINCY,
			hLogoMemDC,
			0,
			0,
			SRCCOPY);

		return;
	}


	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"MenuBlack");

	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	////////////

	if (m_bSingleOn)
	{
		HDC	hSingleOnDC = CBmpMgr::Get_Instance()->Find_Image(m_pSingleOnFrameKey);

		GdiTransparentBlt(
			hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
			60, // 복사 받을 위치 좌표
			140,
			252,	// 복사 받을 이미지의 가로, 세로
			124,
			hSingleOnDC,		// 비트맵을 가지고 있는 DC
			252 * m_tSingleFrame.iFrameStart,			// 비트맵 출력 시작 좌표 LEFT, TOP
			124 * m_tSingleFrame.iMotion,
			252,	// 출력할 비트맵 가로
			124,	// 출력할 비트맵 세로
			RGB(0, 0, 0));	// 제거할 색상 값
	}

	////////////////
	HDC	hSingleDC = CBmpMgr::Get_Instance()->Find_Image(m_pSingleFrameKey);

	GdiTransparentBlt(
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		50, // 복사 받을 위치 좌표
		100,
		320,	// 복사 받을 이미지의 가로, 세로
		116,
		hSingleDC,		// 비트맵을 가지고 있는 DC
		320 * m_tSingleFrame.iFrameStart,			// 비트맵 출력 시작 좌표 LEFT, TOP
		116 * m_tSingleFrame.iMotion,
		320,	// 출력할 비트맵 가로
		116,	// 출력할 비트맵 세로
		RGB(0, 0, 0));	// 제거할 색상 값

	/////////////////
	HDC	hEditorDC = CBmpMgr::Get_Instance()->Find_Image(m_pEditorFrameKey);

	GdiTransparentBlt(
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		500, // 복사 받을 위치 좌표
		150,
		160,	// 복사 받을 이미지의 가로, 세로
		140,
		hEditorDC,		// 비트맵을 가지고 있는 DC
		160 * m_tEditorFrame.iFrameStart,			// 비트맵 출력 시작 좌표 LEFT, TOP
		140 * m_tEditorFrame.iMotion,
		160,	// 출력할 비트맵 가로
		140,	// 출력할 비트맵 세로
		RGB(0, 0, 0));	// 제거할 색상 값
	///////////////

	if (m_bEditorOn)
	{
		HDC	hEditorOnDC = CBmpMgr::Get_Instance()->Find_Image(m_pEditorOnFrameKey);

		GdiTransparentBlt(
			hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
			500, // 복사 받을 위치 좌표
			150,
			204,	// 복사 받을 이미지의 가로, 세로
			132,
			hEditorOnDC,		// 비트맵을 가지고 있는 DC
			204 * m_tEditorOnFrame.iFrameStart,			// 비트맵 출력 시작 좌표 LEFT, TOP
			132 * m_tEditorOnFrame.iMotion,
			204,	// 출력할 비트맵 가로
			132,	// 출력할 비트맵 세로
			RGB(0, 0, 0));	// 제거할 색상 값
	}

	/////////////////
	HDC	hExitDC = CBmpMgr::Get_Instance()->Find_Image(m_pExitFrameKey);

	GdiTransparentBlt(
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		500, // 복사 받을 위치 좌표
		400,
		184,	// 복사 받을 이미지의 가로, 세로
		128,
		hExitDC,		// 비트맵을 가지고 있는 DC
		184 * m_tExitFrame.iFrameStart,			// 비트맵 출력 시작 좌표 LEFT, TOP
		128 * m_tExitFrame.iMotion,
		184,	// 출력할 비트맵 가로
		128,	// 출력할 비트맵 세로
		RGB(0, 0, 0));	// 제거할 색상 값
	//////////////////

	if (m_bExitOn)
	{
		HDC	hExitOnDC = CBmpMgr::Get_Instance()->Find_Image(m_pExitOnFrameKey);

		GdiTransparentBlt(
			hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
			500, // 복사 받을 위치 좌표
			400,
			216,	// 복사 받을 이미지의 가로, 세로
			136,
			hExitOnDC,		// 비트맵을 가지고 있는 DC
			216 * m_tExitOnFrame.iFrameStart,			// 비트맵 출력 시작 좌표 LEFT, TOP
			136 * m_tExitOnFrame.iMotion,
			216,	// 출력할 비트맵 가로
			136,	// 출력할 비트맵 세로
			RGB(0, 0, 0));	// 제거할 색상 값
	}

	////////////////////
	HDC	hSingleTextDC = CBmpMgr::Get_Instance()->Find_Image(m_pSingleTextFrameKey);

	GdiTransparentBlt(
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		180, // 복사 받을 위치 좌표
		220,
		143,	// 복사 받을 이미지의 가로, 세로
		22,
		hSingleTextDC,		// 비트맵을 가지고 있는 DC
		143 * m_tSingleTextFrame.iFrameStart,			// 비트맵 출력 시작 좌표 LEFT, TOP
		22 * m_tSingleTextFrame.iMotion,
		143,	// 출력할 비트맵 가로
		22,	// 출력할 비트맵 세로
		RGB(0, 0, 0));	// 제거할 색상 값

	HDC	hEditorTextDC = CBmpMgr::Get_Instance()->Find_Image(m_pEditorTextFrameKey);

	GdiTransparentBlt(
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		500, // 복사 받을 위치 좌표
		140,
		187,	// 복사 받을 이미지의 가로, 세로
		25,
		hEditorTextDC,		// 비트맵을 가지고 있는 DC
		187 * m_tEditorTextFrame.iFrameStart,			// 비트맵 출력 시작 좌표 LEFT, TOP
		25 * m_tEditorTextFrame.iMotion,
		187,	// 출력할 비트맵 가로
		25,	// 출력할 비트맵 세로
		RGB(0, 0, 0));	// 제거할 색상 값

	HDC	hExitTextDC = CBmpMgr::Get_Instance()->Find_Image(m_pExitTextFrameKey);

	GdiTransparentBlt(
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		550, // 복사 받을 위치 좌표
		380,
		49,	// 복사 받을 이미지의 가로, 세로
		24,
		hExitTextDC,		// 비트맵을 가지고 있는 DC
		49 * m_tExitTextFrame.iFrameStart,			// 비트맵 출력 시작 좌표 LEFT, TOP
		24 * m_tExitTextFrame.iMotion,
		49,	// 출력할 비트맵 가로
		24,	// 출력할 비트맵 세로
		RGB(0, 0, 0));	// 제거할 색상 값




	m_Mouse.Render(hDC);
}

void CMyMenu::Release()
{
	m_Mouse.Release();

	//CObjMgr::Get_Instance()->Delete_ID(OBJ_UI);
}
