#include "stdafx.h"
#include "UI_Stop_Icon.h"
#include "BmpMgr.h"
CUI_Stop_Icon::CUI_Stop_Icon()
{
	InsertBmpFile();
}

CUI_Stop_Icon::~CUI_Stop_Icon()
{
	Release();
}

void CUI_Stop_Icon::Initialize()
{
	//ó�� ũ�� ����
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	__super::Update_Rect();

	m_pFrameKey = L"Stop_Image";
	m_tFrame.iFrameStart = 1;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_UI;
}

int CUI_Stop_Icon::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	return 0;
}

void CUI_Stop_Icon::Late_Update()
{
}

void CUI_Stop_Icon::Render(HDC hDC)
{
	GdiTransparentBlt(
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		m_tRect.left,	// ���� ���� �̹����� ����, ����
		m_tRect.top,
		(int)m_tInfo.fCX,	// ���� ���� �̹����� ����, ����
		(int)m_tInfo.fCY,
		Get_HDC(),		// ��Ʈ���� ������ �ִ� DC
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,	// ����� ��Ʈ�� ����
		(int)m_tInfo.fCY,	// ����� ��Ʈ�� ����
		RGB(0, 0, 0));	// ������ ���� ��
}

void CUI_Stop_Icon::Release()
{
}

void CUI_Stop_Icon::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/CmdIcon/Unituse/Stop_Image.bmp", L"Stop_Image");
}

UIOBJECTTYPE CUI_Stop_Icon::GetType() const
{
	return UI_OBJECT_ICON;
}

int CUI_Stop_Icon::GetDetailType() const
{
	return ICON_STOP;
}
