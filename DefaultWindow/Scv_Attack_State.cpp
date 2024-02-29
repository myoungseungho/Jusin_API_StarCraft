#include "stdafx.h"
#include "Scv_Attack_State.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "TileMgr.h"
CScv_Attack_State::CScv_Attack_State() :m_AttackFileSize(0), m_pFrameKey_Attack(nullptr), m_Offset_Attack(0)
{
}

CScv_Attack_State::~CScv_Attack_State()
{
}

void CScv_Attack_State::Initialize(CObj_Dynamic* _scv)
{
	m_pFrameKey_Attack = L"SCV_Bullet";
	m_tFrame_Attack.iFrameStart = 0;
	m_tFrame_Attack.iFrameEnd = 9;
	m_tFrame_Attack.iMotion = 0;
	m_tFrame_Attack.dwSpeed = 50;
	m_tFrame_Attack.dwTime = GetTickCount();

	m_AttackFileSize = 48;
	m_Offset_Attack = 30;

	POINT scvPoint = _scv->GetMousePT();
	INFO info = _scv->Get_Info();

	int ScvX = info.fX / TILECX;
	int ScvY = info.fY / TILECY;

	int	TileX = scvPoint.x / TILECX;
	int	TileY = scvPoint.y / TILECY;

	Set_Astar(ScvX, ScvY, TileX, TileY);

	m_listPathTile = CTileMgr::Get_Instance()->GetListPath(m_Path);
}

int CScv_Attack_State::Update(CObj_Dynamic* _scv)
{
	Move(_scv);
	return 0;
}

void CScv_Attack_State::Late_Update(CObj_Dynamic* _scv)
{
	Move_Frame(_scv);
}

void CScv_Attack_State::Render(CObj_Dynamic* _scv, HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey_Attack);

	GdiTransparentBlt(
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		(_scv->Get_Rect().left + iScrollX) + m_Offset_Attack, // ���� ���� ��ġ ��ǥ
		(_scv->Get_Rect().top + iScrollY),
		m_AttackFileSize,	// ���� ���� �̹����� ����, ����
		m_AttackFileSize,
		hMemDC,		// ��Ʈ���� ������ �ִ� DC
		m_AttackFileSize * m_tFrame_Attack.iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		m_AttackFileSize * m_tFrame_Attack.iMotion,
		m_AttackFileSize,	// ����� ��Ʈ�� ����
		m_AttackFileSize,	// ����� ��Ʈ�� ����
		RGB(0, 0, 0));	// ������ ���� ��
}

void CScv_Attack_State::Release(CObj_Dynamic* _scv)
{
}

void CScv_Attack_State::Move_Frame(CObj_Dynamic*)
{
	if (m_tFrame_Attack.dwTime + m_tFrame_Attack.dwSpeed < GetTickCount())
	{
		++m_tFrame_Attack.iFrameStart;

		if (m_tFrame_Attack.iFrameStart > m_tFrame_Attack.iFrameEnd)
			m_tFrame_Attack.iFrameStart = 0;

		m_tFrame_Attack.dwTime = GetTickCount();
	}
}
