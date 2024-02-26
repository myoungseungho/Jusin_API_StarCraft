#pragma once
#include "Obj_Dynamic.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Obj_UI.h"
#include "Obj_Static.h"
class CSpawnMgr
{
private:
	CSpawnMgr();
	~CSpawnMgr();
public:
	static		CSpawnMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CSpawnMgr;

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

	template<typename T>
	CObj_Dynamic* Spawn_DynamicObj(DYNAMIC_OBJID _Id, FACTIONSTATE _fId, float _fX, float _fY);

	template<typename T>
	CObj_Static* Spawn_StaticObj(BUILDINGSTATE _Id, FACTIONSTATE _fId, float _fX, float _fY);

	template<typename T>
	CObj_UI* Spawn_UIObj(UI_OBJID _Id);

	template<typename T>
	CObj_UI* Spawn_UIObj(UI_OBJID _Id, float _fX, float _fY);



private:
	static CSpawnMgr* m_pInstance;
};

template<typename T>
inline CObj_Dynamic* CSpawnMgr::Spawn_DynamicObj(DYNAMIC_OBJID _Id, FACTIONSTATE _fId, float _fX, float _fY)
{
	CObj_Dynamic* obj_Dynamic = CAbstractFactory<T>::Create_Dynamic(_fX, _fY);
	CObjMgr::Get_Instance()->Add_Dynamic_Object(_Id, obj_Dynamic);
	obj_Dynamic->Set_FactionState(_fId);
	return obj_Dynamic;
}

template<typename T>
inline CObj_Static* CSpawnMgr::Spawn_StaticObj(BUILDINGSTATE _Id, FACTIONSTATE _fId, float _fX, float _fY)
{
	CObj_Static* obj_Static = CAbstractFactory<T>::Create_Static(_fX, _fY);
	CObjMgr::Get_Instance()->Add_Static_Object(_Id, obj_Static);
	obj_Static->Set_FactionState(_fId);
	return obj_Static;
}


template<typename T>
inline CObj_UI* CSpawnMgr::Spawn_UIObj(UI_OBJID _Id)
{
	CObj_UI* obj_UI = CAbstractFactory<T>::Create_UI();
	CObjMgr::Get_Instance()->Add_UI_Object(_Id, obj_UI);

	return obj_UI;
}

template<typename T>
inline CObj_UI* CSpawnMgr::Spawn_UIObj(UI_OBJID _Id, float _fX, float _fY)
{
	CObj_UI* obj_UI = CAbstractFactory<T>::Create_UI(_fX, _fY);
	CObjMgr::Get_Instance()->Add_UI_Object(_Id, obj_UI);
	obj_UI->Initialize();
	return obj_UI;
}





