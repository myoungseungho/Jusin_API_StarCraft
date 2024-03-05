#include "stdafx.h"
#include "UI_Ghost_Wire_Big.h"
#include "BmpMgr.h"

CUI_Ghost_Wire_Big::CUI_Ghost_Wire_Big()
{
    InsertBmpFile();
}

CUI_Ghost_Wire_Big::~CUI_Ghost_Wire_Big()
{
    Release();
}

void CUI_Ghost_Wire_Big::Initialize()
{
	//ó�� ũ�� ����
	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 64.f;
	__super::Update_Rect();

	m_pFrameKey = L"Ghost_BigWire";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_UI;
}

int CUI_Ghost_Wire_Big::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	return 0;
}

void CUI_Ghost_Wire_Big::Late_Update()
{
}

void CUI_Ghost_Wire_Big::Render(HDC hDC)
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

void CUI_Ghost_Wire_Big::Release()
{
}

UIOBJECTTYPE CUI_Ghost_Wire_Big::GetType() const
{
	return UI_OBJECT_WIRE;
}

int CUI_Ghost_Wire_Big::GetDetailType() const
{
	return WIRE_GHOST_BIG;
}

void CUI_Ghost_Wire_Big::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Wire/Large/Ghost/Ghost_BigWire.bmp", L"Ghost_BigWire");
}
