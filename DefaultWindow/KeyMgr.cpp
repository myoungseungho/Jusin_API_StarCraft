#include "stdafx.h"
#include "KeyMgr.h"
#include "LClick_Mouse.h"
#include "RClick_Mouse.h"
#include "ScrollMgr.h"
CKeyMgr* CKeyMgr::m_pInstance = nullptr;

CKeyMgr::CKeyMgr() : m_Current_Mouse_Click(MOUSE_IDLE_STATE), m_LClick_Mouse(nullptr), m_Cursor_Speed(0.f)
{
	ZeroMemory(m_bKeyState, sizeof(m_bKeyState));
}

CKeyMgr::~CKeyMgr()
{
	Release();
}

void CKeyMgr::Initialize()
{
	m_Cursor_Speed = 12.f;

	m_vecMouseState.push_back(new CLClick_Mouse);
	m_vecMouseState.push_back(new CRClick_Mouse);
}

void CKeyMgr::Update()
{
	if (GetAsyncKeyState(VK_RIGHT))
	{
		CScrollMgr::Get_Instance()->Set_ScrollX(-10.f);
	}

	else if (GetAsyncKeyState(VK_LEFT))
	{
		CScrollMgr::Get_Instance()->Set_ScrollX(10.f);
	}

	else if (GetAsyncKeyState(VK_UP))
	{
		CScrollMgr::Get_Instance()->Set_ScrollY(10.f);

	}

	else if (GetAsyncKeyState(VK_DOWN))
	{
		CScrollMgr::Get_Instance()->Set_ScrollY(-10.f);
	}

	Mouse_HandleInput();
}

void CKeyMgr::Late_Update()
{
	OffSet();
}

void CKeyMgr::Release()
{
	for_each(m_vecMouseState.begin(), m_vecMouseState.end(), Safe_Delete<CCommand*>);
}

bool CKeyMgr::Key_Pressing(int _iKey)
{
	if (GetAsyncKeyState(_iKey) & 0x8000)
		return true;

	return false;
}

// 이전에 눌림이 없고, 현재 누른 경우
bool CKeyMgr::Key_Down(int _iKey)
{
	if ((!m_bKeyState[_iKey]) && (GetAsyncKeyState(_iKey) & 0x8000))
	{
		m_bKeyState[_iKey] = !m_bKeyState[_iKey];
		return true;
	}

	for (int i = 0; i < VK_MAX; ++i)
	{
		if (m_bKeyState[i] && !(GetAsyncKeyState(i) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];
	}

	return false;
}

bool CKeyMgr::Key_Up(int _iKey)
{
	if ((m_bKeyState[_iKey]) && !(GetAsyncKeyState(_iKey) & 0x8000))
	{
		m_bKeyState[_iKey] = !m_bKeyState[_iKey];
		return true;
	}

	for (int i = 0; i < VK_MAX; ++i)
	{
		if (!m_bKeyState[i] && (GetAsyncKeyState(i) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];
	}

	return false;
}


void CKeyMgr::Mouse_HandleInput()
{
	switch (m_Current_Mouse_Click)
	{
	case MOUSE_LCLICK:
		m_vecMouseState[MOUSE_LCLICK]->Execute();
		break;
	case MOUSE_RCLICK:
		m_vecMouseState[MOUSE_RCLICK]->Execute();
		break;
	default:
		break;
	}
}


void CKeyMgr::OffSet()
{
	int	iOffSetMinX = 0;
	int	iOffSetMaxX = WINCX;

	int	iOffSetMinY = 0;
	int	iOffSetMaxY = WINCY;

	POINT	Pt;
	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	if (iOffSetMinX > Pt.x)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_Cursor_Speed);

	if (iOffSetMaxX < Pt.x)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_Cursor_Speed);

	if (iOffSetMinY > Pt.y)
		CScrollMgr::Get_Instance()->Set_ScrollY(m_Cursor_Speed);

	if (iOffSetMaxY < Pt.y)
		CScrollMgr::Get_Instance()->Set_ScrollY(-m_Cursor_Speed);
}