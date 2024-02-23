#include "stdafx.h"
#include "Mouse.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "TileMgr.h"
#include "ObjMgr.h"

CMouse::CMouse()
{
}


CMouse::~CMouse()
{
}

void CMouse::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Cursor/Arrow/Basic_Arrow.bmp", L"Basic_Arrow");

	m_pFrameKey = L"Basic_Arrow";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();

	m_tInfo.fCX = 128.f;
	m_tInfo.fCY = 128.f;

	m_eRender = RENDER_GAMEOBJECT;
}

int CMouse::Update()
{
	POINT	ptMouse{};

	GetCursorPos(&ptMouse);

	// ��ü ��ũ�� �������� Ŭ���̾�Ʈ â ��ǥ�� ��ȯ
	ScreenToClient(g_hWnd, &ptMouse);

	m_tInfo.fX = (float)ptMouse.x;
	m_tInfo.fY = (float)ptMouse.y;

	ShowCursor(FALSE);

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMouse::Late_Update()
{
	KeyInput();
	__super::Move_Frame();
}

void CMouse::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		m_tRect.left, // ���� ���� ��ġ ��ǥ
		m_tRect.top,
		(int)m_tInfo.fCX,	// ���� ���� �̹����� ����, ����
		(int)m_tInfo.fCY,
		hMemDC,		// ��Ʈ���� ������ �ִ� DC
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,	// ����� ��Ʈ�� ����
		(int)m_tInfo.fCY,	// ����� ��Ʈ�� ����
		RGB(0, 0, 0));	// ������ ���� ��
}

void CMouse::Release()
{
}

void CMouse::KeyInput()
{
	//Ŭ�� �Ǿ��� �� ���� üũ
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
	{
		POINT	Pt;
		GetCursorPos(&Pt);
		ScreenToClient(g_hWnd, &Pt);

		Pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		Pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		//��ǥ�� �ش��ϴ� ������ ��ȯ�Ѵ�.

	}
}
