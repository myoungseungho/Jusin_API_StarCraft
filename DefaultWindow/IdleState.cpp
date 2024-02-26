#include "stdafx.h"
#include "IdleState.h"
#include "UIMgr.h"
#include "UI_Move.h"
#include "UI_Stop_Icon.h"
#include "UI_Attack.h"
#include "UI_Build.h"
#include "UI_Advanced_Build.h"
#include "Scv.h"
#include "SpawnMgr.h"

IIdleState::IIdleState()
{
}

IIdleState::~IIdleState()
{
}

void IIdleState::Initialize(CObj_Dynamic* _unit)
{
	CObj_UI* moveIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Move_Icon>(UI_OBJ_ICON, 655.f, 468.f);
	CObj_UI* stopIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Stop_Icon>(UI_OBJ_ICON, 713.f, 468.f);
	CObj_UI* attackIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Attack_Icon>(UI_OBJ_ICON, 768.f, 468.f);

	m_vecIcon.push_back(moveIcon);
	m_vecIcon.push_back(stopIcon);
	m_vecIcon.push_back(attackIcon);

	CScv* scv = dynamic_cast<CScv*>(_unit);
	if (scv != nullptr)
	{
		CObj_UI* buildIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Build_Icon>(UI_OBJ_ICON, 655.f, 570);
		CObj_UI* advancedbuildIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Advanced_Build_Icon>(UI_OBJ_ICON, 715.f, 570);

		m_vecIcon.push_back(buildIcon);
		m_vecIcon.push_back(advancedbuildIcon);
	}

	for (auto iter : m_vecIcon)
	{
		iter->Initialize();
		CUIMgr::Get_Instance()->Set_UI(iter);
	}
}

int IIdleState::Update(CObj_Dynamic*)
{
	return 0;
}

void IIdleState::Late_Update(CObj_Dynamic*)
{
}

void IIdleState::Render(CObj_Dynamic*, HDC hDC)
{
}

void IIdleState::Release(CObj_Dynamic*)
{
}

void IIdleState::Move_Frame()
{
}
