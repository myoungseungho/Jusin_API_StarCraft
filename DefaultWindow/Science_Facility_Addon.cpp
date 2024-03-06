#include "stdafx.h"
#include "Science_Facility_Addon.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
CScience_Facility_Addon::CScience_Facility_Addon() :m_CompleteAddon(false)
{
	InsertBmpFile();
}

CScience_Facility_Addon::~CScience_Facility_Addon()
{
	Release();
}

void CScience_Facility_Addon::Initialize()
{
	//ó�� ũ�� ����
	m_tInfo.fCX = 128.f;
	m_tInfo.fCY = 128.f;

	__super::Update_Rect();

	//�ǹ��� �ִϸ��̼��� ���ݾ�?
	m_pFrameKey = L"Genelab";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 1000;
	m_tFrame.dwTime = GetTickCount();

	m_pFrameConnectKey = L"Genelab_Connect";
	m_tFrameConnect.iFrameStart = 0;
	m_tFrameConnect.iFrameEnd = 4;
	m_tFrameConnect.iMotion = 0;
	m_tFrameConnect.dwSpeed = 50;
	m_tFrameConnect.dwTime = GetTickCount();

	m_eRender = RENDER_BUILDING;

	SetObstcale();

	m_Stat.m_Hp = 750.f;
	m_Stat.m_MaxHp = 750.f;

	lstrcpyW(m_Stat.m_Name, L"Covert Ops");
}

int CScience_Facility_Addon::Update()
{
	__super::Update_Rect();

	if (!m_UIBuilding)
	{
		bool bCanBuild = CTileMgr::Get_Instance()->CanAddBuild(this);
	}
	else if (m_UIBuilding)
		UIBuilding();


	return 0;
}

void CScience_Facility_Addon::Late_Update()
{
	CObj_Static::Move_Frame();

	if (m_CompleteBuilding)
	{
		if (m_CompleteAddon)
			return;

		if (m_tFrameConnect.dwTime + m_tFrameConnect.dwSpeed < GetTickCount())
		{
			++m_tFrameConnect.iFrameStart;

			if (m_tFrameConnect.iFrameStart > m_tFrameConnect.iFrameEnd)
			{
				m_tFrameConnect.iFrameStart = m_tFrameConnect.iFrameEnd;
				m_CompleteAddon = true;
			}

			m_tFrameConnect.dwTime = GetTickCount();
		}
	}
}

void CScience_Facility_Addon::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_CompleteBuilding)
	{
		int grade = m_Stat.m_MaxHp / 6;
		int currentGrade = m_Stat.m_Hp / grade;
		int frame = currentGrade == 0 ? 5 : currentGrade == 1 ? 5 : currentGrade == 2 ? 4 : currentGrade == 3 ? 3
			: currentGrade == 4 ? 2 : currentGrade == 5 ? 1 : currentGrade == 6 ? 0 : 0;

		HDC	hhpDC = CBmpMgr::Get_Instance()->Find_Image(L"Big_Hp");

		GdiTransparentBlt(
			hDC,		// (���� ����)���������� �׸��� �׸� DC ����
			m_tRect.left + iScrollX, // ���� ���� ��ġ ��ǥ
			m_tRect.top + iScrollY + (int)m_tInfo.fCY,
			128,	// ���� ���� �̹����� ����, ����
			5,
			hhpDC,		// ��Ʈ���� ������ �ִ� DC
			128 * frame,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
			5 * m_tFrame.iMotion,
			128,	// ����� ��Ʈ�� ����
			5,	// ����� ��Ʈ�� ����
			RGB(0, 0, 0));	// �����һ��� ��

		HDC	hConnect = CBmpMgr::Get_Instance()->Find_Image(m_pFrameConnectKey);

		GdiTransparentBlt(
			hDC,		// (���� ����)���������� �׸��� �׸� DC ����
			m_tRect.left + iScrollX, // ���� ���� ��ġ ��ǥ
			m_tRect.top + iScrollY+30.f,
			(int)m_tInfo.fCX,	// ���� ���� �̹����� ����, ����
			(int)m_tInfo.fCY,
			hConnect,		// ��Ʈ���� ������ �ִ� DC
			(int)m_tInfo.fCX * m_tFrameConnect.iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
			(int)m_tInfo.fCY * m_tFrameConnect.iMotion,
			(int)m_tInfo.fCX,	// ����� ��Ʈ�� ����
			(int)m_tInfo.fCY,	// ����� ��Ʈ�� ����
			RGB(0, 0, 0));	// ������ ���� ��
	}

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		m_tRect.left + iScrollX, // ���� ���� ��ġ ��ǥ
		m_tRect.top + iScrollY+30.f,
		(int)m_tInfo.fCX,	// ���� ���� �̹����� ����, ����
		(int)m_tInfo.fCY,
		hMemDC,		// ��Ʈ���� ������ �ִ� DC
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,	// ����� ��Ʈ�� ����
		(int)m_tInfo.fCY,	// ����� ��Ʈ�� ����
		RGB(0, 0, 0));	// ������ ���� ��

	if (!m_bCliecked)
		return;

	HDC	hSelectDC = nullptr;
	if (this->Get_FactionState() == FACTION_ALLY)
		hSelectDC = CBmpMgr::Get_Instance()->Find_Image(L"PSelect7");
	else if (this->Get_FactionState() == FACTION_ENEMY)
		hSelectDC = CBmpMgr::Get_Instance()->Find_Image(L"ESelect7");

	GdiTransparentBlt(
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		this->m_tRect.left + iScrollX, // ���� ���� ��ġ ��ǥ
		this->m_tRect.top + iScrollY + 30.f,
		128,	// ���� ���� �̹����� ����, ����
		128,
		hSelectDC,		// ��Ʈ���� ������ �ִ� DC
		0,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		0,
		128,	// ����� ��Ʈ�� ����
		128,	// ����� ��Ʈ�� ����
		RGB(0, 0, 0));	// ������ ���� ��
}

void CScience_Facility_Addon::Release()
{
}

void CScience_Facility_Addon::Spawn_Unit()
{
}

void CScience_Facility_Addon::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Building/Genelab/Genelab.bmp", L"Genelab");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Building/Genelab/Genelab_Connect.bmp", L"Genelab_Connect");

}

BUILDINGSTATE CScience_Facility_Addon::GetType() const
{
	return STATIC_OBJ_SCIENCE_FACILITY_ADDON;
}
