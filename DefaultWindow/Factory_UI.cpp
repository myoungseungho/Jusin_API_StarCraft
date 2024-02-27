#include "stdafx.h"
#include "Factory_UI.h"
#include "BmpMgr.h"
CFactory_UI::CFactory_UI()
{
    InsertBmpFile();
}

CFactory_UI::~CFactory_UI()
{
    Release();
}

void CFactory_UI::Initialize()
{
}

int CFactory_UI::Update()
{
    return 0;
}

void CFactory_UI::Late_Update()
{
}

void CFactory_UI::Release()
{
}

ICONSTATE CFactory_UI::GetType() const
{
    return ICON_END;
}

void CFactory_UI::InsertBmpFile()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Building/Factory/Factory.bmp", L"Factory");
}
