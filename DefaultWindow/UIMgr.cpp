#include "stdafx.h"
#include "UIMgr.h"
#include "BmpMgr.h"
#include "Obj_Dynamic.h"
#include "UnitControlMgr.h"
#include "SpawnMgr.h"
#include "UI_Move.h"
#include "UI_Stop_Icon.h"
#include "UI_Attack.h"
#include "UI_Build.h"
#include "UI_Advanced_Build.h"

CUIMgr* CUIMgr::m_pInstance = nullptr;

CUIMgr::CUIMgr()
{
}

CUIMgr::~CUIMgr()
{
}

void CUIMgr::Initialize()
{
	CObj_UI* moveIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Move_Icon>(UI_OBJ_ICON, 655.f, 468.f);
	CObj_UI* stopIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Stop_Icon>(UI_OBJ_ICON, 713.f, 468.f);
	CObj_UI* attackIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Attack_Icon>(UI_OBJ_ICON, 768.f, 468.f);
	CObj_UI* buildIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Build_Icon>(UI_OBJ_ICON, 655.f, 570);
	CObj_UI* advancedbuildIcon = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Advanced_Build_Icon>(UI_OBJ_ICON, 715.f, 570);

	m_vecUnitUI[DYANMIC_OBJ_SCV].push_back(moveIcon);
	m_vecUnitUI[DYANMIC_OBJ_SCV].push_back(stopIcon);
	m_vecUnitUI[DYANMIC_OBJ_SCV].push_back(attackIcon);
	m_vecUnitUI[DYANMIC_OBJ_SCV].push_back(buildIcon);
	m_vecUnitUI[DYANMIC_OBJ_SCV].push_back(advancedbuildIcon);
}

void CUIMgr::Render(HDC hDC)
{
	vector<CObj_Dynamic*> vecUnit = CUnitControlMgr::Get_Instance()->GetVecUnit();

	if (vecUnit.size() == 0)
		return;

	for (auto iter : m_vecUnitUI[vecUnit.back()->GetType()])
	{
		RECT m_tRect = iter->Get_Rect();
		INFO m_tInfo = iter->Get_Info();
		FRAME* m_tFrame = iter->Get_Frame();
		GdiTransparentBlt(
			hDC,		// (���� ����)���������� �׸��� �׸� DC ����
			m_tRect.left,	// ���� ���� �̹����� ����, ����
			m_tRect.top,
			(int)m_tInfo.fCX,	// ���� ���� �̹����� ����, ����
			(int)m_tInfo.fCY,
			iter->Get_HDC(),		// ��Ʈ���� ������ �ִ� DC
			(int)m_tInfo.fCX * m_tFrame->iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
			(int)m_tInfo.fCY * m_tFrame->iMotion,
			(int)m_tInfo.fCX,	// ����� ��Ʈ�� ����
			(int)m_tInfo.fCY,	// ����� ��Ʈ�� ����
			RGB(0, 0, 0));	// ������ ���� ��
	}
}
