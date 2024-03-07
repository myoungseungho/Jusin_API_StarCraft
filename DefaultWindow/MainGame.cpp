#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "TileMgr.h"
#include "SpawnMgr.h"
#include "AStarMgr.h"
#include "UnitControlMgr.h"
#include "TechTreeMgr.h"
#include "UIMgr.h"
#include "SoundMgr.h"
#include "EconomyMgr.h"
CMainGame::CMainGame() : m_iFPS(0), m_dwTime(GetTickCount())
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/back.bmp", L"Back");

	CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);

//#ifdef _DEBUG
//
//	if (::AllocConsole() == TRUE)
//	{
//		FILE* nfp[3];
//		freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
//		freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
//		freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
//		std::ios::sync_with_stdio();
//	}
//
//#endif // _DEBUG
}

void CMainGame::Update()
{
	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{
	CSceneMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Scroll_Lock();
}

void CMainGame::Render()
{
	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);	// 윈도우 상단에 글씨를 출력해줌

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}
	
	//백버퍼
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Back");
	BitBlt(m_hDC,
		0, 0, WINCX, WINCY,
		hMemDC,
		0,
		0,
		SRCCOPY);	

	CSceneMgr::Get_Instance()->Render(hMemDC);
	//CKeyMgr::Get_Instance()->Render(hMemDC);
}

void CMainGame::Release()
{	
	CTileMgr::Get_Instance()->Destroy_Instance();
	CBmpMgr::Get_Instance()->Destroy_Instance();
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();
	CLineMgr::Get_Instance()->Destroy_Instance();
	CSceneMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Destroy_Instance();
	CSpawnMgr::Get_Instance()->Destroy_Instance();
	CAStarMgr::Get_Instance()->Destroy_Instance();
	CUnitControlMgr::Get_Instance()->Destroy_Instance();
	CTechTreeMgr::Get_Instance()->Destroy_Instance();
	CUIMgr::Get_Instance()->Destroy_Instance();
	CSoundMgr::Get_Instance()->Destroy_Instance();
	CEconomyMgr::Get_Instance()->Destroy_Instance();
	ReleaseDC(g_hWnd, m_hDC);	
}

