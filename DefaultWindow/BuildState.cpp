#include "stdafx.h"
#include "BuildState.h"
IBuildState::IBuildState()
{
}

IBuildState::~IBuildState()
{
}

void IBuildState::Initialize(CObj_Dynamic* _scv)
{

}

int IBuildState::Update(CObj_Dynamic* _scv)
{
    return 0;
}

void IBuildState::Late_Update(CObj_Dynamic*)
{
}

void IBuildState::Render(CObj_Dynamic*, HDC hDC)
{
}

void IBuildState::Release(CObj_Dynamic*)
{
}

void IBuildState::Move_Frame(CObj_Dynamic* _scv)
{
	if (m_tFrame_Attack.dwTime + m_tFrame_Attack.dwSpeed < GetTickCount())
	{
		++m_tFrame_Attack.iFrameStart;

		if (m_tFrame_Attack.iFrameStart > m_tFrame_Attack.iFrameEnd)
			m_tFrame_Attack.iFrameStart = 0;

		m_tFrame_Attack.dwTime = GetTickCount();
	}
}

