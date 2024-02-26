#include "stdafx.h"
#include "UIMgr.h"
#include "BmpMgr.h"
#include "Obj_Dynamic.h"
#include "UnitControlMgr.h"
CUIMgr* CUIMgr::m_pInstance = nullptr;

CUIMgr::CUIMgr()
{
}

CUIMgr::~CUIMgr()
{
}

void CUIMgr::Initialize()
{

}

void CUIMgr::Render(HDC hDC)
{
	for (auto iter : m_vecUI)
	{
		RECT m_tRect = iter->Get_Rect();
		INFO m_tInfo = iter->Get_Info();
		FRAME* m_tFrame = iter->Get_Frame();
		GdiTransparentBlt(
			hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
			m_tRect.left,	// 복사 받을 이미지의 가로, 세로
			m_tRect.top,
			(int)m_tInfo.fCX,	// 복사 받을 이미지의 가로, 세로
			(int)m_tInfo.fCY,
			iter->Get_HDC(),		// 비트맵을 가지고 있는 DC
			(int)m_tInfo.fCX * m_tFrame->iFrameStart,			// 비트맵 출력 시작 좌표 LEFT, TOP
			(int)m_tInfo.fCY * m_tFrame->iMotion,
			(int)m_tInfo.fCX,	// 출력할 비트맵 가로
			(int)m_tInfo.fCY,	// 출력할 비트맵 세로
			RGB(0, 0, 0));	// 제거할 색상 값
	}
}

void CUIMgr::Set_UI(CObj_UI* _uiObj)
{
	m_vecUI.push_back(_uiObj);
}

void CUIMgr::Init_VecUI()
{
	m_vecUI.clear();
}
