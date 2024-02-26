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
		GdiTransparentBlt(
			hDC,		// (���� ����)���������� �׸��� �׸� DC ����
			0, // ���� ���� ��ġ ��ǥ
			0,
			WINCX,	// ���� ���� �̹����� ����, ����
			WINCY,
			iter->Get_HDC(),		// ��Ʈ���� ������ �ִ� DC
			0,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
			0,
			WINCX,	// ����� ��Ʈ�� ����
			WINCY,	// ����� ��Ʈ�� ����
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
