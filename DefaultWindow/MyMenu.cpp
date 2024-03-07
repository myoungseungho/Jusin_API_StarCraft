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

		//�̱��÷��� ȣ����
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
		//������ ȣ����
		else if (mouseX >= 500 && mouseX <= 660.f && mouseY >= 150.f && mouseY <= 290.f)
		{
			m_bSingleOn = false;
			m_bEditorOn = true;
			m_bExitOn = false;
		}
		//����Ʈ ȣ����
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
			hDC,		// (���� ����)���������� �׸��� �׸� DC ����
			60, // ���� ���� ��ġ ��ǥ
			140,
			252,	// ���� ���� �̹����� ����, ����
			124,
			hSingleOnDC,		// ��Ʈ���� ������ �ִ� DC
			252 * m_tSingleFrame.iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
			124 * m_tSingleFrame.iMotion,
			252,	// ����� ��Ʈ�� ����
			124,	// ����� ��Ʈ�� ����
			RGB(0, 0, 0));	// ������ ���� ��
	}

	////////////////
	HDC	hSingleDC = CBmpMgr::Get_Instance()->Find_Image(m_pSingleFrameKey);

	GdiTransparentBlt(
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		50, // ���� ���� ��ġ ��ǥ
		100,
		320,	// ���� ���� �̹����� ����, ����
		116,
		hSingleDC,		// ��Ʈ���� ������ �ִ� DC
		320 * m_tSingleFrame.iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		116 * m_tSingleFrame.iMotion,
		320,	// ����� ��Ʈ�� ����
		116,	// ����� ��Ʈ�� ����
		RGB(0, 0, 0));	// ������ ���� ��

	/////////////////
	HDC	hEditorDC = CBmpMgr::Get_Instance()->Find_Image(m_pEditorFrameKey);

	GdiTransparentBlt(
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		500, // ���� ���� ��ġ ��ǥ
		150,
		160,	// ���� ���� �̹����� ����, ����
		140,
		hEditorDC,		// ��Ʈ���� ������ �ִ� DC
		160 * m_tEditorFrame.iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		140 * m_tEditorFrame.iMotion,
		160,	// ����� ��Ʈ�� ����
		140,	// ����� ��Ʈ�� ����
		RGB(0, 0, 0));	// ������ ���� ��
	///////////////

	if (m_bEditorOn)
	{
		HDC	hEditorOnDC = CBmpMgr::Get_Instance()->Find_Image(m_pEditorOnFrameKey);

		GdiTransparentBlt(
			hDC,		// (���� ����)���������� �׸��� �׸� DC ����
			500, // ���� ���� ��ġ ��ǥ
			150,
			204,	// ���� ���� �̹����� ����, ����
			132,
			hEditorOnDC,		// ��Ʈ���� ������ �ִ� DC
			204 * m_tEditorOnFrame.iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
			132 * m_tEditorOnFrame.iMotion,
			204,	// ����� ��Ʈ�� ����
			132,	// ����� ��Ʈ�� ����
			RGB(0, 0, 0));	// ������ ���� ��
	}

	/////////////////
	HDC	hExitDC = CBmpMgr::Get_Instance()->Find_Image(m_pExitFrameKey);

	GdiTransparentBlt(
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		500, // ���� ���� ��ġ ��ǥ
		400,
		184,	// ���� ���� �̹����� ����, ����
		128,
		hExitDC,		// ��Ʈ���� ������ �ִ� DC
		184 * m_tExitFrame.iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		128 * m_tExitFrame.iMotion,
		184,	// ����� ��Ʈ�� ����
		128,	// ����� ��Ʈ�� ����
		RGB(0, 0, 0));	// ������ ���� ��
	//////////////////

	if (m_bExitOn)
	{
		HDC	hExitOnDC = CBmpMgr::Get_Instance()->Find_Image(m_pExitOnFrameKey);

		GdiTransparentBlt(
			hDC,		// (���� ����)���������� �׸��� �׸� DC ����
			500, // ���� ���� ��ġ ��ǥ
			400,
			216,	// ���� ���� �̹����� ����, ����
			136,
			hExitOnDC,		// ��Ʈ���� ������ �ִ� DC
			216 * m_tExitOnFrame.iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
			136 * m_tExitOnFrame.iMotion,
			216,	// ����� ��Ʈ�� ����
			136,	// ����� ��Ʈ�� ����
			RGB(0, 0, 0));	// ������ ���� ��
	}

	////////////////////
	HDC	hSingleTextDC = CBmpMgr::Get_Instance()->Find_Image(m_pSingleTextFrameKey);

	GdiTransparentBlt(
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		180, // ���� ���� ��ġ ��ǥ
		220,
		143,	// ���� ���� �̹����� ����, ����
		22,
		hSingleTextDC,		// ��Ʈ���� ������ �ִ� DC
		143 * m_tSingleTextFrame.iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		22 * m_tSingleTextFrame.iMotion,
		143,	// ����� ��Ʈ�� ����
		22,	// ����� ��Ʈ�� ����
		RGB(0, 0, 0));	// ������ ���� ��

	HDC	hEditorTextDC = CBmpMgr::Get_Instance()->Find_Image(m_pEditorTextFrameKey);

	GdiTransparentBlt(
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		500, // ���� ���� ��ġ ��ǥ
		140,
		187,	// ���� ���� �̹����� ����, ����
		25,
		hEditorTextDC,		// ��Ʈ���� ������ �ִ� DC
		187 * m_tEditorTextFrame.iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		25 * m_tEditorTextFrame.iMotion,
		187,	// ����� ��Ʈ�� ����
		25,	// ����� ��Ʈ�� ����
		RGB(0, 0, 0));	// ������ ���� ��

	HDC	hExitTextDC = CBmpMgr::Get_Instance()->Find_Image(m_pExitTextFrameKey);

	GdiTransparentBlt(
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		550, // ���� ���� ��ġ ��ǥ
		380,
		49,	// ���� ���� �̹����� ����, ����
		24,
		hExitTextDC,		// ��Ʈ���� ������ �ִ� DC
		49 * m_tExitTextFrame.iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		24 * m_tExitTextFrame.iMotion,
		49,	// ����� ��Ʈ�� ����
		24,	// ����� ��Ʈ�� ����
		RGB(0, 0, 0));	// ������ ���� ��




	m_Mouse.Render(hDC);
}

void CMyMenu::Release()
{
	m_Mouse.Release();

	//CObjMgr::Get_Instance()->Delete_ID(OBJ_UI);
}
