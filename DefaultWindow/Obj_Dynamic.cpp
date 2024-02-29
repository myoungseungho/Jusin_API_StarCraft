#include "stdafx.h"
#include "Obj_Dynamic.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
CObj_Dynamic::CObj_Dynamic() : m_CurrentState(NON_STATE), m_bDead(false), m_OnceDead(false)
{
}

CObj_Dynamic::~CObj_Dynamic()
{
	Release();
}


void CObj_Dynamic::Release()
{
	for_each(m_vecState.begin(), m_vecState.end(), Safe_Delete<IState*>);
}

void CObj_Dynamic::Move_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			m_tFrame.iFrameStart = 0;
		}

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
	ChangeState(_sId);
}

bool CObj_Dynamic::CheckEnemy()
{
	if (m_pTarget != nullptr)
		return true;

	list<CObj*>* pList = CObjMgr::Get_Instance()->GetDynamic_Obj_List();
	float nearDistnace = (numeric_limits<float>::max)();
	CObj* target = nullptr;

	for (size_t i = 0; i < DYNAMIC_OBJ_END; i++)
	{
		for (auto iter : pList[i])
		{
			if (iter == this || iter->Get_FactionState() == this->Get_FactionState())
				continue;

			float distance = sqrt((iter->Get_Info().fX - m_tInfo.fX) * (iter->Get_Info().fX - m_tInfo.fX) + (iter->Get_Info().fY - m_tInfo.fY) * (iter->Get_Info().fY - m_tInfo.fY));

			if (distance < nearDistnace)
			{
				nearDistnace = distance;
				target = iter;
			}
		}
	}

	if (m_Stat.m_DetectionRange > nearDistnace)
	{
		if (m_CurrentState != ATTACK_STATE)
		{
			ChangeState(ATTACK_STATE);
			m_pTarget = target;
			return true;
		}
	}

	m_pTarget = nullptr;
	return false;
}

