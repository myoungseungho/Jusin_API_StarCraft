#include "stdafx.h"
#include "UIMgr.h"
#include "BmpMgr.h"
CUIMgr* CUIMgr::m_pInstance = nullptr;

CUIMgr::CUIMgr()
{
}

CUIMgr::~CUIMgr()
{
}

void CUIMgr::Initialize()
{
	/*CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/back.bmp", L"Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Single/MainUI.bmp", L"MainUI");*/
}

void CUIMgr::Render(HDC hDC)
{
	//HDC	hUIDC = CBmpMgr::Get_Instance()->Find_Image(L"MainUI");
	GdiTransparentBlt(
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		0, // ���� ���� ��ġ ��ǥ
		0,
		WINCX,	// ���� ���� �̹����� ����, ����
		WINCY,
		hUIDC,		// ��Ʈ���� ������ �ִ� DC
		0,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		0,
		WINCX,	// ����� ��Ʈ�� ����
		WINCY,	// ����� ��Ʈ�� ����
		RGB(0, 0, 0));	// ������ ���� ��
}
