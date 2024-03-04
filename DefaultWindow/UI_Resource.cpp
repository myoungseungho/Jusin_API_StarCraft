#include "stdafx.h"
#include "UI_Resource.h"
#include "BmpMgr.h"
#include "EconomyMgr.h"
CUI_Resource::CUI_Resource()
{
}

CUI_Resource::~CUI_Resource()
{
}

void CUI_Resource::Initialize()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CurrentResource.bmp", L"CurrentResource");

    m_eRender = RENDER_UI;
}

int CUI_Resource::Update()
{
    return 0;
}

void CUI_Resource::Late_Update()
{
}

void CUI_Resource::Render(HDC hDC)
{
	HDC	hUIDC = CBmpMgr::Get_Instance()->Find_Image(L"CurrentResource");
	GdiTransparentBlt(
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		550, // ���� ���� ��ġ ��ǥ
		10,
		261,	// ���� ���� �̹����� ����, ����
		29,
		hUIDC,		// ��Ʈ���� ������ �ִ� DC
		0,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		0,
		261,	// ����� ��Ʈ�� ����
		29,	// ����� ��Ʈ�� ����
		RGB(0, 0, 0));	// ������ ���� ��


}

void CUI_Resource::Release()
{
}

UIOBJECTTYPE CUI_Resource::GetType() const
{
    return UIOBJECTTYPE();
}

int CUI_Resource::GetDetailType() const
{
    return 0;
}

void CUI_Resource::InsertBmpFile()
{
}
