#include "stdafx.h"
#include "Nuclear_Target.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
CNuclear_Target::CNuclear_Target()
{
    InsertBmpFile();
}

CNuclear_Target::~CNuclear_Target()
{
    Release();
}

void CNuclear_Target::Initialize()
{
	m_eRender = RENDER_UI;

	//ó�� ũ�� ����
	m_tInfo.fCX = 8.f;
	m_tInfo.fCY = 8.f;

	m_pFrameKey = L"NuclearTarget";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();
}

int CNuclear_Target::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    __super::Update_Rect();

    return 0;
}

void CNuclear_Target::Late_Update()
{
}

void CNuclear_Target::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		m_tRect.left + iScrollX, // ���� ���� ��ġ ��ǥ
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,	// ���� ���� �̹����� ����, ����
		(int)m_tInfo.fCY,
		hMemDC,		// ��Ʈ���� ������ �ִ� DC
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,	// ����� ��Ʈ�� ����
		(int)m_tInfo.fCY,	// ����� ��Ʈ�� ����
		RGB(255, 255, 255));	// ������ ���� ��
}

DYNAMIC_OBJID CNuclear_Target::GetType() const
{
    return DYNAMIC_OBJ_NUCLEAR_TARGET;
}

void CNuclear_Target::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Nuketarg/NuclearTarget.bmp", L"NuclearTarget");
}
