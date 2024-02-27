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

void IBuildState::Move_Frame()
{
}
