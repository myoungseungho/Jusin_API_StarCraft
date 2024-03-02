#pragma once
#include "Define.h"
#include "Obj_UI.h"
#include "Obj_Static.h"
#include "UI_IconMgr.h"
#include "UI_WireMgr.h"
#include "UI_Text_Mgr.h"
class CUIMgr
{
private:
	CUIMgr();
	~CUIMgr();
public:
	static		CUIMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CUIMgr;
		}

		return m_pInstance;
	}

	static void	Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
public:
	void Initialize();
	void Late_Update();
	void Render(HDC hDC);
	void Release();
public:
	void OnClickObj(CObj*);
	void OnClickIcon(CObj*);
	void OnDragObj();
	void SetClear_Dynamic_Obj();
	void SetClear_StaticObj();
	void SetClear_CurrentBuilding() { m_UI_IconMgr->SetClear_CurrentBuilding(); };
	void DynamicSetUI(DYNAMIC_OBJID);
	void StaticSetUI(BUILDINGSTATE);

	UI_BUILDINGSTATE GetBuilding() { return m_UI_IconMgr->GetBuilding(); }
private:
	static CUIMgr* m_pInstance;

	CUI_IconMgr* m_UI_IconMgr;
	CUI_WireMgr* m_UI_WireMgr;
	CUI_Text_Mgr* m_UI_TextMgr;
};

