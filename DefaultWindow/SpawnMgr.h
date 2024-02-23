#pragma once
#include "Obj_Dynamic.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Obj_UI.h"
class CSpawnMgr
{
public:
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
	CObj_Dynamic* Spawn_DynamicObj(DYNAMIC_OBJID _Id, float _fX, float _fY);

	template<typename T>
	CObj_Dynamic* Spawn_DynamicObj(DYNAMIC_OBJID _Id, STATEID _sId, float _fX, float _fY);

	template<typename T>
	CObj_UI* Spawn_UIObj(UI_OBJID _Id);

	template<typename T>
	CObj_UI* Spawn_UIObj(UI_OBJID _Id, float _fX, float _fY);



private:
	static CSpawnMgr* m_pInstance;
};

template<typename T>
inline CObj_Dynamic* CSpawnMgr::Spawn_DynamicObj(DYNAMIC_OBJID _Id, float _fX, float _fY)
{
	CObj_Dynamic* obj_Dynamic = CAbstractFactory<T>::Create_Dynamic(_fX, _fY);
	CObjMgr::Get_Instance()->Add_Dynamic_Object(_Id, obj_Dynamic);

	return obj_Dynamic;
}

template<typename T>
inline CObj_Dynamic* CSpawnMgr::Spawn_DynamicObj(DYNAMIC_OBJID _Id, STATEID _sId, float _fX, float _fY)
{
	CObj_Dynamic* obj_Dynamic = CAbstractFactory<T>::Create_Dynamic(_fX, _fY);
	obj_Dynamic->ChangeState((*CStateMgr::Get_Instance()->GetVecObjState(_Id))[_sId]);
	CObjMgr::Get_Instance()->Add_Dynamic_Object(_Id, obj_Dynamic);

	return obj_Dynamic;
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

	return obj_UI;
}





