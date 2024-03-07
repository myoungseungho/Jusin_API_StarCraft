#include "stdafx.h"
#include "Barrack.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "Obj_Dynamic.h"
#include "SpawnMgr.h"
#include "Marine.h"
#include "FireBat.h"
#include "Medic.h"
#include "Ghost.h"
CBarrack::CBarrack()
{
	InsertBmpFile();
}

CBarrack::~CBarrack()
{
	Release();
}

void CBarrack::Initialize()
{
	//ó�� ũ�� ����
	m_tInfo.fCX = 192.f;
	m_tInfo.fCY = 160.f;

	__super::Update_Rect();

	//�ǹ��� �ִϸ��̼��� ���ݾ�?
	m_pFrameKey = L"Barrack";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 1000;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDER_BUILDING;

	m_Stat.m_MaxHp = 1000.f;
	m_Stat.m_Hp = 1000.f;
	SetObstcale();

	lstrcpyW(m_Stat.m_Name, L"Barrack");
}

int CBarrack::Update()
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

void CBarrack::Late_Update()
{
	CObj_Static::Move_Frame();
}

void CBarrack::Render(HDC hDC)
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
			m_tRect.left + iScrollX + 25.f, // ���� ���� ��ġ ��ǥ
			m_tRect.top + iScrollY + (int)m_tInfo.fCY - 30.f,
			128,	// ���� ���� �̹����� ����, ����
			5,
			hhpDC,		// ��Ʈ���� ������ �ִ� DC
			128 * frame,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
			5 * m_tFrame.iMotion,
			128,	// ����� ��Ʈ�� ����
			5,	// ����� ��Ʈ�� ����
			RGB(0, 0, 0));	// ������ ���� ��
	}

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

	if (!m_bCliecked)
		return;

	HDC	hSelectDC = nullptr;
	if (this->Get_FactionState() == FACTION_ALLY)
		hSelectDC = CBmpMgr::Get_Instance()->Find_Image(L"PSelect8");
	else if (this->Get_FactionState() == FACTION_ENEMY)
		hSelectDC = CBmpMgr::Get_Instance()->Find_Image(L"ESelect8");

	GdiTransparentBlt(
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		this->m_tRect.left + iScrollX + 25.f, // ���� ���� ��ġ ��ǥ
		this->m_tRect.top + iScrollY + 10.f,
		148,	// ���� ���� �̹����� ����, ����
		148,
		hSelectDC,		// ��Ʈ���� ������ �ִ� DC
		0,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		0,
		148,	// ����� ��Ʈ�� ����
		148,	// ����� ��Ʈ�� ����
		RGB(0, 0, 0));	// ������ ���� ��
}

void CBarrack::Release()
{
}

void CBarrack::Spawn_Unit(DYNAMIC_OBJID _objId)
{
	CObj_Dynamic* obj = nullptr;
	if (_objId == DYNAMIC_OBJ_MARINE)
	{
		obj = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMarine>(DYNAMIC_OBJ_MARINE, FACTION_ALLY, m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY * 0.5f + 10.f);
	}
	else if (_objId == DYNAMIC_OBJ_FIREBAT)
	{
		obj = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CFireBat>(DYNAMIC_OBJ_FIREBAT, FACTION_ALLY, m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY * 0.5f + 10.f);
	}
	else if (_objId == DYNAMIC_OBJ_MEDIC)
	{
		obj = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CMedic>(DYNAMIC_OBJ_MEDIC, FACTION_ALLY, m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY * 0.5f + 10.f);
	}
	else if (_objId == DYNAMIC_OBJ_GHOST)
	{
		obj = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CGhost>(DYNAMIC_OBJ_GHOST, FACTION_ALLY, m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY * 0.5f + 10.f);
	}

	m_vecWaitUnit.push_back(obj);
}

void CBarrack::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Building/Barrack/Barrack.bmp", L"Barrack");
}

BUILDINGSTATE CBarrack::GetType() const
{
	return STATIC_OBJ_BARRACK;
}
