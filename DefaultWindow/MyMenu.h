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

	//�̱��÷���
	TCHAR* m_pSingleFrameKey;
	FRAME		m_tSingleFrame;

	//�̱��÷��� �ؽ�Ʈ
	TCHAR* m_pSingleTextFrameKey;
	FRAME		m_tSingleTextFrame;

	//�̱��÷��� ��
	TCHAR* m_pSingleOnFrameKey;
	FRAME		m_tSingleOnFrame;

	//������
	TCHAR* m_pEditorFrameKey;
	FRAME		m_tEditorFrame;

	//������ �ؽ�Ʈ
	TCHAR* m_pEditorTextFrameKey;
	FRAME		m_tEditorTextFrame;

	//������ ��
	TCHAR* m_pEditorOnFrameKey;
	FRAME		m_tEditorOnFrame;

	//����Ʈ
	TCHAR* m_pExitFrameKey;
	FRAME		m_tExitFrame;

	//����Ʈ �ؽ�Ʈ
	TCHAR* m_pExitTextFrameKey;
	FRAME		m_tExitTextFrame;

	//����Ʈ ��
	TCHAR* m_pExitOnFrameKey;
	FRAME		m_tExitOnFrame;

	CMouse m_Mouse;

	bool m_bSingleOn;
	bool m_bEditorOn;
	bool m_bExitOn;
	bool m_InitLogoOn;
	DWORD m_CurrentTime;
};

