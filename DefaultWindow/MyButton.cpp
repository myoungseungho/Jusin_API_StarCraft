#include "stdafx.h"
#include "MyButton.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

CMyButton::CMyButton()
	: m_iDrawID(0)
{
}

CMyButton::~CMyButton()
{
	Release();
}

void CMyButton::Initialize()
{
	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 150.f;

	m_eRender = RENDER_UI;
}

int CMyButton::Update()
{

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMyButton::Late_Update()
{
	POINT	ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	if (PtInRect(&m_tRect, ptMouse))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (!lstrcmp(L"Start", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE);

			else if (!lstrcmp(L"Edit", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(SC_EDIT);

			else if (!lstrcmp(L"Exit", m_pFrameKey))
				DestroyWindow(g_hWnd);

			return;
		}

		m_iDrawID = 1;
	}

	else
		m_iDrawID = 0;


}

void CMyButton::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		m_tRect.left, // 복사 받을 위치 좌표
		m_tRect.top,
		(int)m_tInfo.fCX,	// 복사 받을 이미지의 가로, 세로
		(int)m_tInfo.fCY,
		hMemDC,		// 비트맵을 가지고 있는 DC
		m_iDrawID * (int)m_tInfo.fCX,			// 비트맵 출력 시작 좌표 LEFT, TOP
		0,
		(int)m_tInfo.fCX,	// 출력할 비트맵 가로
		(int)m_tInfo.fCY,	// 출력할 비트맵 세로
		RGB(255, 255, 255));	// 제거할 색상 값
}

void CMyButton::Release()
{

}
