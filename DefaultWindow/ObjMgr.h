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
	void    Add_UI_Object(UI_OBJID eID, CObj* pObj);

	int		Update();
	void	Late_Update();
	void	Render(HDC hDC);
	void	Release();

	void	Delete_ID_DynamicObj(DYNAMIC_OBJID eId);
	void	Delete_ID_StaticObj(BUILDINGSTATE eId);
	void	Delete_ID_UIObj(UI_OBJID eId);

public:
	CObj* Get_Target(float _fX, float _fY);
	CObj* Get_Target_UI(float _fX, float _fY);
	vector<CObj*> Get_Targets(POINT _initPoint, POINT _goalPoint);

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
	list<CObj*>				m_UI_Obj_List[UI_OBJ_END];

	list<CObj*>				m_RenderList[RENDER_END];

	static CObjMgr* m_pInstance;
};

