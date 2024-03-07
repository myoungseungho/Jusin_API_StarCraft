#include "stdafx.h"
#include "FireBat_Attack_State.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CFireBat_Attack_State::CFireBat_Attack_State() : m_AttackFileSize(0), m_Offset_Attack(0)
{
}

CFireBat_Attack_State::~CFireBat_Attack_State()
{
}

void CFireBat_Attack_State::Initialize(CObj_Dynamic* _fireBat)
{
	m_pFrameCopy = _fireBat->Get_Frame();
	m_pFrameKeyCopy = _fireBat->Get_FrameKey();

	*m_pFrameKeyCopy = L"Firebat_Work_Up_Right_90";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 15;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 50;
	m_pFrameCopy->dwTime = GetTickCount();

	m_pFrameKey_Attack = L"FireBat_Bullet_Right";
	m_tFrame_Attack.iFrameStart = 0;
	m_tFrame_Attack.iFrameEnd = 11;
	m_tFrame_Attack.iMotion = 0;
	m_tFrame_Attack.dwSpeed = 50;
	m_tFrame_Attack.dwTime = GetTickCount();

	m_AttackFileSize = 224;
	m_Offset_Attack = -90;

	_fireBat->SetAttackRun(false);
}

int CFireBat_Attack_State::Update(CObj_Dynamic* _fireBat)
{
	//Ÿ���� �ִٸ�
	if (_fireBat->Get_Target())
	{
		//���� ���ݻ����Ÿ��� �ȵ�
		if (!_fireBat->GetAttackRun())
			MoveUntilAttackDistance(_fireBat);
		//���ݹ��� ���� ��
		else
		{
			Attack(_fireBat);
		}
	}
	//Ÿ���� ���ٸ�
	else
	{

		if (!_fireBat->CheckEnemy())
			_fireBat->ChangeStateWithMouse(_fireBat->GetMousePT(), WALK_STATE);

			//_fireBat->ChangeState(IDLE_STATE);
	}

	return 0;
}

void CFireBat_Attack_State::Late_Update(CObj_Dynamic* _fireBat)
{
	if (_fireBat->GetAttackRun())
		Move_Frame(_fireBat);
}

void CFireBat_Attack_State::Render(CObj_Dynamic* _fireBat, HDC hDC)
{
	if (!_fireBat->GetAttackRun())
		return;

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey_Attack);

	GdiTransparentBlt(
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		(_fireBat->Get_Rect().left + iScrollX) + m_Offset_Attack, // ���� ���� ��ġ ��ǥ
		(_fireBat->Get_Rect().top + iScrollY) + m_Offset_Attack,
		m_AttackFileSize,	// ���� ���� �̹����� ����, ����
		m_AttackFileSize,
		hMemDC,		// ��Ʈ���� ������ �ִ� DC
		m_AttackFileSize * m_tFrame_Attack.iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		m_AttackFileSize * m_tFrame_Attack.iMotion,
		m_AttackFileSize,	// ����� ��Ʈ�� ����
		m_AttackFileSize,	// ����� ��Ʈ�� ����
		RGB(0, 0, 0));	// ������ ���� ��
}

void CFireBat_Attack_State::Release(CObj_Dynamic*)
{
}


void CFireBat_Attack_State::Move_Frame(CObj_Dynamic* _fireBat)
{
	if (m_tFrame_Attack.dwTime + m_tFrame_Attack.dwSpeed < GetTickCount())
	{
		++m_tFrame_Attack.iFrameStart;

		if (m_tFrame_Attack.iFrameStart > m_tFrame_Attack.iFrameEnd)
		{
			m_tFrame_Attack.iFrameStart = 0;
		}

		m_tFrame_Attack.dwTime = GetTickCount();
	}
}

void CFireBat_Attack_State::Attack(CObj_Dynamic* _unit)
{
	IAttackState::Attack(_unit);
}

