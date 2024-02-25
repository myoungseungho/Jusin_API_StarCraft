#include "stdafx.h"
#include "Tile.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CTile::CTile() : m_iDrawID(0), m_iOption(0)
{
}

CTile::~CTile()
{
	Release();
}

void CTile::Initialize()
{
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;
	m_eRender = RENDER_BACKGROUND;
}

int CTile::Update()
{
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CTile::Late_Update()
{
}

void CTile::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Grid");

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		m_tRect.left + iScrollX, // ���� ���� ��ġ ��ǥ
		m_tRect.top + iScrollY,
		TILECX,	// ���� ���� �̹����� ����, ����
		TILECY,
		hMemDC,		// ��Ʈ���� ������ �ִ� DC
		TILECX * m_iDrawID,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		0,
		TILECX,	// ����� ��Ʈ�� ����
		TILECY,	// ����� ��Ʈ�� ����
		RGB(255, 255, 255));	// ������ ���� ��
}

void CTile::Release()
{
}
