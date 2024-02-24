#include "stdafx.h"
#include "Obj_Dynamic.h"
CObj_Dynamic::CObj_Dynamic() : m_CurrentState(NON_STATE), m_bDead(false)
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

void CObj_Dynamic::ChangeState(STATEID _sId)
{
	m_CurrentState = _sId;
	m_vecState[_sId]->Initialize(this);
}

void CObj_Dynamic::ChangeStateWithMouse(POINT _pt, STATEID _sId)
{
	m_MousePT = _pt;
	//ChangeState(_sId);
	Initialize();
}

