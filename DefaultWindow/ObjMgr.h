#pragma once

#include "Obj.h"
#include "Obj_Dynamic.h"

class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	void	Add_Dynamic_Object(DYNAMIC_OBJID eID, CObj_Dynamic* pObj);
	int		Update();
	void	Late_Update();
	void	Render(HDC hDC);
	void	Release();

	void	Delete_ID_DynamicObj(DYNAMIC_OBJID eId);

public:
	CObj*	Get_Target(DYNAMIC_OBJID eID, CObj_Dynamic* pObj);

public:
	static		CObjMgr*		Get_Instance()
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
	list<CObj*>				m_ObjList[DYNAMIC_OBJ_END];
	list<CObj_Dynamic*>		m_Dynamic_Obj_List[DYNAMIC_OBJ_END];
	list<CObj*>				m_RenderList[RENDER_END];
	list<CObj_Dynamic*>		m_Dynamic_RenderList[RENDER_END];
		
	static CObjMgr*	m_pInstance;

};

