#include "stdafx.h"
#include "Marine_Attack_State.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
CMarine_Attack_State::CMarine_Attack_State() : m_AttackFileSize(0), m_Offset_Attack(0)
{
}

CMarine_Attack_State::~CMarine_Attack_State()
{
}

void CMarine_Attack_State::Initialize(CObj_Dynamic* _marine)
{
	m_pFrameCopy = _marine->Get_Frame();
	m_pFrameKeyCopy = _marine->Get_FrameKey();

	*m_pFrameKeyCopy = L"Marine_Walk_Right_90";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 17;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 50;
	m_pFrameCopy->dwTime = GetTickCount();

	m_pFrameKey_Attack = L"Tspark";
	m_tFrame_Attack.iFrameStart = 0;
	m_tFrame_Attack.iFrameEnd = 15;
	m_tFrame_Attack.iMotion = 0;
	m_tFrame_Attack.dwSpeed = 20;
	m_tFrame_Attack.dwTime = GetTickCount();

	m_AttackFileSize = 40;

	m_bAttackDistanceIn = false;
}

int CMarine_Attack_State::Update(CObj_Dynamic* _marine)
{
	////���� �����Ÿ��� ����
	//if (!_marine->CheckEnemy())
	//{
	//	_marine->ChangeState(IDLE_STATE);
	//	return 0;
	//}
	//else
	//{
	//	//���� �����Ÿ��� ����
	//	//���� ���ݹ������� ����
	//	if (!m_bAttackDistanceIn)
	//		MoveUntilAttackDistance(_marine);
	//	//���ݹ��� ���� ��
	//	else
	//	{
	//		Attack(_marine);
	//	}
	//	return 0;
	//}

	//Ÿ���� �ִٸ�
	if (_marine->Get_Target())
	{
		//���� ���ݻ����Ÿ��� �ȵ�
		if (!m_bAttackDistanceIn)
			MoveUntilAttackDistance(_marine);
		//���ݹ��� ���� ��
		else
		{
			Attack(_marine);
		}
	}
	//Ÿ���� ���ٸ�
	else
	{
		if (!_marine->CheckEnemy())
			_marine->ChangeState(IDLE_STATE);
	}

	return 0;
}

void CMarine_Attack_State::Late_Update(CObj_Dynamic* _marine)
{
	if (m_bAttackDistanceIn)
		Move_Frame(_marine);
}

void CMarine_Attack_State::Render(CObj_Dynamic* _marine, HDC hDC)
{
	if (!m_bAttackDistanceIn)
		return;

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey_Attack);

	GdiTransparentBlt(
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		_marine->Get_Target()->Get_Rect().left + iScrollX + m_Offset_Attack, // ���� ���� ��ġ ��ǥ
		_marine->Get_Target()->Get_Rect().top + iScrollY + m_Offset_Attack,
		m_AttackFileSize,	// ���� ���� �̹����� ����, ����
		m_AttackFileSize,
		hMemDC,		// ��Ʈ���� ������ �ִ� DC
		m_AttackFileSize * m_tFrame_Attack.iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		m_AttackFileSize * m_tFrame_Attack.iMotion,
		m_AttackFileSize,	// ����� ��Ʈ�� ����
		m_AttackFileSize,	// ����� ��Ʈ�� ����
		RGB(0, 0, 0));	// ������ ���� ��
}

void CMarine_Attack_State::Release(CObj_Dynamic*)
{
}

void CMarine_Attack_State::Move_Frame(CObj_Dynamic* _marine)
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

void CMarine_Attack_State::Attack(CObj_Dynamic* _unit)
{
	CObj* target = _unit->Get_Target();

	if (target == nullptr || target->Get_Dead())
	{
		m_bAttackDistanceIn = false;
		_unit->ChangeState(IDLE_STATE);
		return;
	}

	if (m_tFrame_Attack.iFrameStart == 0)
	{
		if (target != nullptr && !target->Get_Dead())
		{
			CObj_Dynamic* dynamicObj = dynamic_cast<CObj_Dynamic*>(target);
			if (dynamicObj != nullptr)
				dynamic_cast<CObj_Dynamic*>(target)->Set_Damage(_unit->Get_Stat().m_Attack);
		}
	}
}


void CMarine_Attack_State::MoveUntilAttackDistance(CObj_Dynamic* _marine)
{
	CObj* target = _marine->Get_Target();

	// �̵��ؾ� �� ���� ���� ���
	float dirX = target->Get_Info().fX - _marine->Get_Info().fX;
	float dirY = target->Get_Info().fY - _marine->Get_Info().fY;
	float length = sqrt(dirX * dirX + dirY * dirY);

	if (length < _marine->Get_Stat().m_AttackRange) { // ��ǥ������ �Ÿ��� �ӵ����� Ŭ ���, �̵� ����

		m_bAttackDistanceIn = true;

		m_pFrameCopy = _marine->Get_Frame();
		m_pFrameKeyCopy = _marine->Get_FrameKey();

		*m_pFrameKeyCopy = L"Mairen_Attack_Right_90";
		m_pFrameCopy->iFrameStart = 0;
		m_pFrameCopy->iFrameEnd = 5;
		m_pFrameCopy->iMotion = 0;
		m_pFrameCopy->dwSpeed = 100;
		m_pFrameCopy->dwTime = GetTickCount();
	}
	else
	{
		// ���� ���� ���Ϳ� �ӵ��� ����Ͽ� �̵�
		float speed = _marine->Get_Stat().m_fSpeed; // ������ �ӵ� ��
		dirX = (dirX / length) * speed;
		dirY = (dirY / length) * speed;
		_marine->Set_PosX(dirX);
		_marine->Set_PosY(dirY);
	}
}
