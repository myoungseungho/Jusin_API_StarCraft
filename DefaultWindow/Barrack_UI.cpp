#include "stdafx.h"
#include "Barrack_UI.h"
#include "BmpMgr.h"

CBarrack_UI::CBarrack_UI()
{
    InsertBmpFile();
}

CBarrack_UI::~CBarrack_UI()
{
    Release();
}

void CBarrack_UI::Initialize()
{
}

int CBarrack_UI::Update()
{
    return 0;
}

void CBarrack_UI::Late_Update()
{
}

void CBarrack_UI::Release()
{
}

ICONSTATE CBarrack_UI::GetType() const
{
    return ICON_END;
}

void CBarrack_UI::InsertBmpFile()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Building/Barrack/Barrack.bmp", L"Barrack");
}
