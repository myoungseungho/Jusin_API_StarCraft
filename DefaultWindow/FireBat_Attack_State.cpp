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

	m_bAttackDistanceIn = false;
}

int CFireBat_Attack_State::Update(CObj_Dynamic* _fireBat)
{
	//타겟이 있다면
	if (_fireBat->Get_Target())
	{
		//아직 공격사정거리는 안됨
		if (!m_bAttackDistanceIn)
			MoveUntilAttackDistance(_fireBat);
		//공격범위 까지 감
		else
		{
			Attack(_fireBat);
		}
	}
	//타겟이 없다면
	else
	{
		if (!_fireBat->CheckEnemy())
			_fireBat->ChangeState(IDLE_STATE);
	}

	return 0;
}

void CFireBat_Attack_State::Late_Update(CObj_Dynamic* _fireBat)
{
	if (m_bAttackDistanceIn)
		Move_Frame(_fireBat);
}

void CFireBat_Attack_State::Render(CObj_Dynamic* _fireBat, HDC hDC)
{
	if (!m_bAttackDistanceIn)
		return;

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey_Attack);

	GdiTransparentBlt(
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		(_fireBat->Get_Rect().left + iScrollX) + m_Offset_Attack, // 복사 받을 위치 좌표
		(_fireBat->Get_Rect().top + iScrollY) + m_Offset_Attack,
		m_AttackFileSize,	// 복사 받을 이미지의 가로, 세로
		m_AttackFileSize,
		hMemDC,		// 비트맵을 가지고 있는 DC
		m_AttackFileSize * m_tFrame_Attack.iFrameStart,			// 비트맵 출력 시작 좌표 LEFT, TOP
		m_AttackFileSize * m_tFrame_Attack.iMotion,
		m_AttackFileSize,	// 출력할 비트맵 가로
		m_AttackFileSize,	// 출력할 비트맵 세로
		RGB(0, 0, 0));	// 제거할 색상 값
}

void CFireBat_Attack_State::Release(CObj_Dynamic*)
{
}


void CFireBat_Attack_State::MoveUntilAttackDistance(CObj_Dynamic* _fireBat)
{
	CObj* target = _fireBat->Get_Target();

	// 이동해야 할 방향 벡터 계산
	float dirX = target->Get_Info().fX - _fireBat->Get_Info().fX;
	float dirY = target->Get_Info().fY - _fireBat->Get_Info().fY;
	float length = sqrt(dirX * dirX + dirY * dirY);

	if (length < _fireBat->Get_Stat().m_AttackRange) { // 목표까지의 거리가 속도보다 클 경우, 이동 실행

		m_bAttackDistanceIn = true;

		m_pFrameCopy = _fireBat->Get_Frame();
		m_pFrameKeyCopy = _fireBat->Get_FrameKey();

		*m_pFrameKeyCopy = L"Firebat_Attack_Right_90";
		m_pFrameCopy->iFrameStart = 0;
		m_pFrameCopy->iFrameEnd = 0;
		m_pFrameCopy->iMotion = 0;
		m_pFrameCopy->dwSpeed = 200;
		m_pFrameCopy->dwTime = GetTickCount();
	}
	else
	{
		// 단위 방향 벡터와 속도를 사용하여 이동
		float speed = _fireBat->Get_Stat().m_fSpeed; // 적당한 속도 값
		dirX = (dirX / length) * speed;
		dirY = (dirY / length) * speed;
		_fireBat->Set_PosX(dirX);
		_fireBat->Set_PosY(dirY);
	}
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
	CObj* target = _unit->Get_Target();

	if (target == nullptr || target->Get_Dead())
	{
		m_bAttackDistanceIn = false;
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
