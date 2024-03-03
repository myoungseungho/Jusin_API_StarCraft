#include "stdafx.h"
#include "Medic_Attack_State.h"

CMedic_Attack_State::CMedic_Attack_State()
{
}

CMedic_Attack_State::~CMedic_Attack_State()
{
}

void CMedic_Attack_State::Initialize(CObj_Dynamic* _medic)
{

	m_pFrameCopy = _medic->Get_Frame();
	m_pFrameKeyCopy = _medic->Get_FrameKey();

	*m_pFrameKeyCopy = L"Medic_Walk_Down_Right_150";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 13;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 100;
	m_pFrameCopy->dwTime = GetTickCount();
}

int CMedic_Attack_State::Update(CObj_Dynamic* _medic)
{
	//타겟이 있다면
	if (_medic->Get_Target())
	{
		//아직 공격사정거리는 안됨
		if (!_medic->GetAttackRun())
			MoveUntilAttackDistance(_medic);
		//공격범위 까지 감
		else
		{
			Attack(_medic);
		}
	}
	//타겟이 없다면
	else
	{
		_medic->Set_Clear_Target();
		if (!_medic->CheckEnemy())
			_medic->ChangeState(IDLE_STATE);
	}
	return 0;
}

void CMedic_Attack_State::Late_Update(CObj_Dynamic*)
{
}

void CMedic_Attack_State::Render(CObj_Dynamic*, HDC hDC)
{
}

void CMedic_Attack_State::Release(CObj_Dynamic*)
{
}

void CMedic_Attack_State::Move_Frame(CObj_Dynamic*)
{
}
