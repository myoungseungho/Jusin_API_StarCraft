#include "stdafx.h"
#include "Obj_UI.h"

CObj_UI::CObj_UI()
{
}

CObj_UI::~CObj_UI()
{
}

void CObj_UI::Initialize()
{
}

int CObj_UI::Update()
{
	return 0;
}

void CObj_UI::Late_Update()
{
}

void CObj_UI::Render(HDC hDC)
{
}

void CObj_UI::Release()
{
}

void CObj_UI::Move_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;

		m_tFrame.dwTime = GetTickCount();
	}
}
