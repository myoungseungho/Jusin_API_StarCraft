#include "stdafx.h"
#include "Depot_UI.h"
#include "BmpMgr.h"

CDepot_UI::CDepot_UI()
{
    InsertBmpFile();
}

CDepot_UI::~CDepot_UI()
{
    Release();
}

void CDepot_UI::Initialize()
{
}

int CDepot_UI::Update()
{
    return 0;
}

void CDepot_UI::Late_Update()
{
}

void CDepot_UI::Release()
{
}

ICONSTATE CDepot_UI::GetType() const
{
    return ICON_END;
}

void CDepot_UI::InsertBmpFile()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Building/Depot/Depot.bmp", L"Depot");
}
