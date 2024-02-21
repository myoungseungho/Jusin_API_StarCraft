#include "stdafx.h"
#include "MyEdit.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "TileMgr.h"

CMyEdit::CMyEdit()
{
}


CMyEdit::~CMyEdit()
{
	Release();
}

void CMyEdit::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/Tile.bmp", L"Tile");

	CTileMgr::Get_Instance()->Initialize();
}

int CMyEdit::Update()
{
	CTileMgr::Get_Instance()->Update();

	return 0;
}

void CMyEdit::Late_Update()
{
	CTileMgr::Get_Instance()->Late_Update();
	Key_Input();
}

void CMyEdit::Render(HDC hDC)
{
	CTileMgr::Get_Instance()->Render(hDC);
}

void CMyEdit::Release()
{
}

void CMyEdit::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		CScrollMgr::Get_Instance()->Set_ScrollY(5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		CScrollMgr::Get_Instance()->Set_ScrollY(-5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
	{
		POINT	Pt;
		GetCursorPos(&Pt);
		ScreenToClient(g_hWnd, &Pt);
		
		Pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		Pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();
		
		CTileMgr::Get_Instance()->Picking(Pt, 1, 0);
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F1))
		CTileMgr::Get_Instance()->Save_Tile();

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F2))
		CTileMgr::Get_Instance()->Load_Tile();
}
