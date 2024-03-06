#pragma once

#include "Obj.h"
#include "Obj_Dynamic.h"

class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	void	Add_Dynamic_Object(DYNAMIC_OBJID eID, CObj* pObj);
	void    Add_Static_Object(BUILDINGSTATE eID, CObj* pObj);
	void    Add_UI_Object(UIOBJECTTYPE eID, CObj* pObj);

	int		Update();
	void	Late_Update();
	void	Render(HDC hDC);
	void	Release();

	void	Delete_ID_DynamicObj(DYNAMIC_OBJID eId);
	void	Delete_ID_StaticObj(BUILDINGSTATE eId);
	void	Delete_ID_UIObj(UIOBJECTTYPE eId);

public:
	CObj* Get_Target(float _fX, float _fY);
	CObj* Get_Target_UI(float _fX, float _fY);
	vector<CObj*> Get_Targets(POINT _initPoint, POINT _goalPoint);
	list<CObj*>* GetDynamic_Obj_List() { return m_Dynamic_Obj_List; };
	list<CObj*>* GetStatic_Obj_List() { return m_Static_Obj_List; };
	list<CObj*>* GetUI_Obj_List() { return m_UI_Obj_List; };
	list<CObj*> GetNearUnit(CObj_Dynamic*, float);
public:
	static		CObjMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;

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

private:
	list<CObj*>				m_Dynamic_Obj_List[DYNAMIC_OBJ_END];
	list<CObj*>				m_Static_Obj_List[STATIC_OBJ_END];
	list<CObj*>				m_UI_Obj_List[UI_OBJECT_END];
	list<CObj*>				m_RenderList[RENDER_END];

	static CObjMgr* m_pInstance;
};

