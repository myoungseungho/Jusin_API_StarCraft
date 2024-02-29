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

	_marine->SetAttackRun(false);
}

int CMarine_Attack_State::Update(CObj_Dynamic* _marine)
{
	//타겟이 있다면
	if (_marine->Get_Target())
	{
		//아직 공격사정거리는 안됨
		if (!_marine->GetAttackRun())
			MoveUntilAttackDistance(_marine);
		//공격범위 까지 감
		else
		{
			Attack(_marine);
		}
	}
	//타겟이 없다면
	else
	{
		_marine->Set_Clear_Target();
		if (!_marine->CheckEnemy())
			_marine->ChangeState(IDLE_STATE);
	}

	return 0;
}

void CMarine_Attack_State::Late_Update(CObj_Dynamic* _marine)
{
	if (_marine->GetAttackRun())
		Move_Frame(_marine);
}

void CMarine_Attack_State::Render(CObj_Dynamic* _marine, HDC hDC)
{
	if (!_marine->GetAttackRun())
		return;

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey_Attack);

	GdiTransparentBlt(
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		_marine->Get_Target()->Get_Rect().left + iScrollX + m_Offset_Attack, // 복사 받을 위치 좌표
		_marine->Get_Target()->Get_Rect().top + iScrollY + m_Offset_Attack,
		m_AttackFileSize,	// 복사 받을 이미지의 가로, 세로
		m_AttackFileSize,
		hMemDC,		// 비트맵을 가지고 있는 DC
		m_AttackFileSize * m_tFrame_Attack.iFrameStart,			// 비트맵 출력 시작 좌표 LEFT, TOP
		m_AttackFileSize * m_tFrame_Attack.iMotion,
		m_AttackFileSize,	// 출력할 비트맵 가로
		m_AttackFileSize,	// 출력할 비트맵 세로
		RGB(0, 0, 0));	// 제거할 색상 값
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
		_unit->SetAttackRun(false);
		_unit->ChangeState(IDLE_STATE);
		_unit->Set_Clear_Target();
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

