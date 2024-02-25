#include "stdafx.h"
#include "KeyMgr.h"
#include "LClick_Mouse.h"
#include "RClick_Mouse.h"
#include "Drag_LMouse_Long.h"
#include "ScrollMgr.h"
CKeyMgr* CKeyMgr::m_pInstance = nullptr;

CKeyMgr::CKeyMgr() : m_Current_Mouse_Click(MOUSE_IDLE_STATE), m_Cursor_Speed(0.f), m_bHasSelectUnit(false), m_dwTime(0), m_deltaTime(0), m_IsDragLClick(false)
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
	m_deltaTime = 1 / 65;
	m_vecMouseCommand.push_back(new CLClick_Mouse);
	m_vecMouseCommand.push_back(new CRClick_Mouse);
	m_vecMouseCommand.push_back(new Drag_LMouse_Long);
}

void CKeyMgr::Update()
{

	KeyBoard_HandleInput();

	//왼쪽 누르고 있으면
	if (Key_Pressing(VK_LBUTTON))
	{
		if (m_IsDragLClick == false)
		{
			m_IsDragLClick = true;

			POINT	Pt;
			GetCursorPos(&Pt);
			ScreenToClient(g_hWnd, &Pt);

			Pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
			Pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

			m_Current_Mouse_Click = MOUSE_LDRAG;
			m_vecMouseCommand[MOUSE_LDRAG]->Initialize(Pt);
		}
	}

	//뗐을 때
	if (Key_Up(VK_LBUTTON))
	{
		/*	m_Current_Mouse_Click = MOUSE_LCLICK;
			m_Current_Mouse_Click = MOUSE_IDLE_STATE;*/
	}


	if (Key_Up(VK_RBUTTON))
	{
		/*m_Current_Mouse_Click = MOUSE_RCLICK;
		m_Current_Mouse_Click = MOUSE_IDLE_STATE;*/
	}

	Mouse_HandleInput();
}

void CKeyMgr::Late_Update()
{
	OffSet();
}

void CKeyMgr::Release()
{
	for_each(m_vecMouseCommand.begin(), m_vecMouseCommand.end(), Safe_Delete<CCommand*>);
}


void CKeyMgr::Mouse_HandleInput()
{
	switch (m_Current_Mouse_Click)
	{
	case MOUSE_LCLICK:
		m_vecMouseCommand[MOUSE_LCLICK]->Execute();
		break;
	case MOUSE_RCLICK:
		m_vecMouseCommand[MOUSE_RCLICK]->Execute();
		break;
	case MOUSE_LDRAG:
		m_vecMouseCommand[MOUSE_LDRAG]->Execute();
	default:
		break;
	}
}

void CKeyMgr::KeyBoard_HandleInput()
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

//이전에 눌린적이 있고, 호출 시점에는 눌려 있지 있는 상태
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