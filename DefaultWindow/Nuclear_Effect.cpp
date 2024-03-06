#include "stdafx.h"
#include "Nuclear_Effect.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
CNuclear_Effect::CNuclear_Effect()
{
	InsertBmpFile();
}

CNuclear_Effect::~CNuclear_Effect()
{
	Release();
}

void CNuclear_Effect::Initialize()
{
	m_eRender = RENDER_UI;
	m_Collision = COLLISION_NOT;
	//ó�� ũ�� ����
	m_tInfo.fCX = 252.f;
	m_tInfo.fCY = 252.f;

	m_pFrameKey = L"NuclearHit";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 25;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
}

int CNuclear_Effect::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		m_bDead = true;

	__super::Update_Rect();
	return 0;
}

void CNuclear_Effect::Late_Update()
{
	Move_Frame();
}

void CNuclear_Effect::Render(HDC hDC)
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
		RGB(0, 0, 0));	// ������ ���� ��
}

DYNAMIC_OBJID CNuclear_Effect::GetType() const
{
	return DYNAMIC_OBJ_NUCLEAR_EFFECT;
}

void CNuclear_Effect::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Nuke/NuclearHit.bmp", L"NuclearHit");
}
