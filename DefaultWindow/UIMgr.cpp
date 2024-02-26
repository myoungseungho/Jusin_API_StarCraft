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
			hDC,		// (���� ����)���������� �׸��� �׸� DC ����
			m_tRect.left,	// ���� ���� �̹����� ����, ����
			m_tRect.top,
			(int)m_tInfo.fCX,	// ���� ���� �̹����� ����, ����
			(int)m_tInfo.fCY,
			iter->Get_HDC(),		// ��Ʈ���� ������ �ִ� DC
			(int)m_tInfo.fCX * m_tFrame->iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
			(int)m_tInfo.fCY * m_tFrame->iMotion,
			(int)m_tInfo.fCX,	// ����� ��Ʈ�� ����
			(int)m_tInfo.fCY,	// ����� ��Ʈ�� ����
			RGB(0, 0, 0));	// ������ ���� ��
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
