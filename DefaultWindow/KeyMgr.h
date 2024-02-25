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
	void Release();
public:
	bool		Key_Pressing(int _iKey);
	bool		Key_Down(int _iKey);
	bool		Key_Up(int _iKey);
public:
	void Set_Mouse_State(MOUSESTATE _mId) { m_Current_Mouse_Click = _mId; }
	void OffSet();

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

private:
	static CKeyMgr* m_pInstance;
	bool			m_bKeyState[VK_MAX];
	vector<CCommand*> m_vecMouseState;

	MOUSESTATE m_Current_Mouse_Click;
	CCommand* m_LClick_Mouse;

	float m_Cursor_Speed;
};

