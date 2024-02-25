#pragma once

#include "Define.h"
#include "Command.h"
#include "LClick_Mouse.h"
class CKeyMgr
{
private:
	CKeyMgr();
	~CKeyMgr();

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC);
	void Release();
public:
	bool		Key_Pressing(int _iKey);
	bool		Key_Down(int _iKey);
	bool		Key_Up(int _iKey);
	//bool		Key_Drag(int _iKey);
public:
	void Set_Mouse_State(MOUSESTATE _mId) { m_Current_Mouse_Click = _mId; }
	void OffSet();
	void Set_bSelectUnit(bool _bUnit) { m_bHasSelectUnit = _bUnit; };
	bool Get_bSelectUnit() { return m_bHasSelectUnit; }

public:
	static		CKeyMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CKeyMgr;

		return m_pInstance;
	}

	static void	Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
public:
	void Mouse_HandleInput();
	void KeyBoard_HandleInput();

private:
	static CKeyMgr* m_pInstance;
	bool			m_bKeyState[VK_MAX];
	vector<CCommand*> m_vecMouseCommand;

	MOUSESTATE m_Current_Mouse_Click;

	bool m_bHasSelectUnit;
	bool m_IsLClick;
	bool m_IsDragClick;
	float m_Cursor_Speed;
	float m_Threshold_Drag;
	DWORD	m_dwTime;
	DWORD	m_deltaTime;

	POINT m_InitPoint;
	POINT m_CurrentPoint;
};

