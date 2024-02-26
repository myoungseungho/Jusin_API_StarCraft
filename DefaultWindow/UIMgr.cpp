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
	//	hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
	//	0, // 복사 받을 위치 좌표
	//	0,
	//	WINCX,	// 복사 받을 이미지의 가로, 세로
	//	WINCY,
	//	hUIDC,		// 비트맵을 가지고 있는 DC
	//	0,			// 비트맵 출력 시작 좌표 LEFT, TOP
	//	0,
	//	WINCX,	// 출력할 비트맵 가로
	//	WINCY,	// 출력할 비트맵 세로
	//	RGB(0, 0, 0));	// 제거할 색상 값
}
