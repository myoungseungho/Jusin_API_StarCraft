#include "stdafx.h"
#include "BackGround.h"
#include "BmpMgr.h"
CBackGround::CBackGround()
{
}
CBackGround::~CBackGround()
{
}
void CBackGround::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Single/MainUI.bmp", L"MainUI");

	m_eRender = RENDER_UI;
}

int CBackGround::Update()
{
    return 0;
}

void CBackGround::Late_Update()
{
}

void CBackGround::Render(HDC hDC)
{
	HDC	hUIDC = CBmpMgr::Get_Instance()->Find_Image(L"MainUI");
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

void CBackGround::Release()
{
}

ICONSTATE CBackGround::GetType() const
{
	return ICON_END;
}
