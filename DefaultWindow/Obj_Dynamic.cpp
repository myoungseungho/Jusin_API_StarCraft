#include "stdafx.h"
#include "Obj_Dynamic.h"
#include "StateMgr.h"
CObj_Dynamic::CObj_Dynamic() : m_CurrentState(nullptr) , m_bDead(false)
{
}

CObj_Dynamic::~CObj_Dynamic()
{
}


void CObj_Dynamic::Move_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;

		m_tFrame.dwTime = GetTickCount();
	}
}

void CObj_Dynamic::ChangeState(IState* _newState)
{
	m_CurrentState = _newState;
	m_CurrentState->Initialize(this);
}

void CObj_Dynamic::ChangeStateByType(STATEID _sId)
{
	IState* newState = CStateMgr::Get_Instance()->GetState(this->GetType(), _sId);
	ChangeState(newState);
}
