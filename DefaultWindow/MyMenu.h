#pragma once
#include "Scene.h"
#include "Mouse.h"
class CMyMenu :	public CScene
{
public:
	CMyMenu();
	virtual ~CMyMenu();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:

	//싱글플레이
	TCHAR* m_pSingleFrameKey;
	FRAME		m_tSingleFrame;

	//싱글플레이 텍스트
	TCHAR* m_pSingleTextFrameKey;
	FRAME		m_tSingleTextFrame;

	//싱글플레이 온
	TCHAR* m_pSingleOnFrameKey;
	FRAME		m_tSingleOnFrame;

	//에디터
	TCHAR* m_pEditorFrameKey;
	FRAME		m_tEditorFrame;

	//에디터 텍스트
	TCHAR* m_pEditorTextFrameKey;
	FRAME		m_tEditorTextFrame;

	//에디터 온
	TCHAR* m_pEditorOnFrameKey;
	FRAME		m_tEditorOnFrame;

	//엑시트
	TCHAR* m_pExitFrameKey;
	FRAME		m_tExitFrame;

	//엑시트 텍스트
	TCHAR* m_pExitTextFrameKey;
	FRAME		m_tExitTextFrame;

	//엑시트 온
	TCHAR* m_pExitOnFrameKey;
	FRAME		m_tExitOnFrame;

	CMouse m_Mouse;

	bool m_bSingleOn;
	bool m_bEditorOn;
	bool m_bExitOn;
	bool m_InitLogoOn;
	DWORD m_CurrentTime;
};

