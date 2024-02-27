#include "stdafx.h"
#include "StarPort_UI.h"
#include "BmpMgr.h"

CStarPort_UI::CStarPort_UI()
{
	InsertBmpFile();
}

CStarPort_UI::~CStarPort_UI()
{
	Release();
}

void CStarPort_UI::Initialize()
{
}

int CStarPort_UI::Update()
{
	return 0;
}

void CStarPort_UI::Late_Update()
{
}

void CStarPort_UI::Release()
{
}

ICONSTATE CStarPort_UI::GetType() const
{
	return ICON_END;
}

void CStarPort_UI::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Building/Starport/StarPort.bmp", L"StarPort");
}
