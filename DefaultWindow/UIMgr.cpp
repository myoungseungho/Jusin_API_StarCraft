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
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CmdIcon/Unituse/Move_Image.bmp", L"Move_Image");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CmdIcon/Unituse/Stop_Image.bmp", L"Stop_Image");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CmdIcon/Unituse/Attack_Image.bmp", L"Attack_Image");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CmdIcon/Unituse/Build_Image.bmp", L"Build_Image");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CmdIcon/Unituse/Advanced_Image.bmp", L"Advanced_Image");
}

void CUIMgr::Render(HDC hDC)
{
	//HDC	hUIDC = CBmpMgr::Get_Instance()->Find_Image(L"MainUI");
	//GdiTransparentBlt(
	//	hDC,		// (���� ����)���������� �׸��� �׸� DC ����
	//	0, // ���� ���� ��ġ ��ǥ
	//	0,
	//	WINCX,	// ���� ���� �̹����� ����, ����
	//	WINCY,
	//	hUIDC,		// ��Ʈ���� ������ �ִ� DC
	//	0,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
	//	0,
	//	WINCX,	// ����� ��Ʈ�� ����
	//	WINCY,	// ����� ��Ʈ�� ����
	//	RGB(0, 0, 0));	// ������ ���� ��
}
