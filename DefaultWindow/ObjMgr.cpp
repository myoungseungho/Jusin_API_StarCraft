#include "stdafx.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}

CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Add_Dynamic_Object(DYNAMIC_OBJID eID, CObj* pObj)
{
	if (DYNAMIC_OBJ_END <= eID || nullptr == pObj)
		return;

	m_Dynamic_Obj_List[eID].push_back(pObj);
}

void CObjMgr::Add_Static_Object(BUILDINGSTATE eID, CObj* pObj)
{
	if (STATIC_OBJ_END <= eID || nullptr == pObj)
		return;

	m_Static_Obj_List[eID].push_back(pObj);
}

void CObjMgr::Add_UI_Object(UI_OBJID eID, CObj* pObj)
{
	if (UI_OBJ_END <= eID || nullptr == pObj)
		return;

	m_UI_Obj_List[eID].push_back(pObj);
}


int CObjMgr::Update()
{
	for (size_t i = 0; i < DYNAMIC_OBJ_END; ++i)
	{
		for (auto iter = m_Dynamic_Obj_List[i].begin();
			iter != m_Dynamic_Obj_List[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_Dynamic_Obj_List[i].erase(iter);
			}
			else
				++iter;
		}
	}

	for (size_t i = 0; i < STATIC_OBJ_END; ++i)
	{
		for (auto iter = m_Static_Obj_List[i].begin();
			iter != m_Static_Obj_List[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_Static_Obj_List[i].erase(iter);
			}
			else
				++iter;
		}
	}

	for (size_t i = 0; i < UI_OBJ_END; ++i)
	{
		for (auto iter = m_UI_Obj_List[i].begin();
			iter != m_UI_Obj_List[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_UI_Obj_List[i].erase(iter);
			}
			else
				++iter;
		}
	}
	return 0;
}

void CObjMgr::Late_Update()
{
	for (size_t i = 0; i < DYNAMIC_OBJ_END; ++i)
	{
		for (auto& iter : m_Dynamic_Obj_List[i])
		{
			iter->Late_Update();

			if (m_Dynamic_Obj_List[i].empty())
				break;

			RENDERID eID = iter->Get_RenderID();
			m_RenderList[eID].push_back(iter);
		}
	}

	for (size_t i = 0; i < STATIC_OBJ_END; ++i)
	{
		for (auto& iter : m_Static_Obj_List[i])
		{
			iter->Late_Update();

			if (m_Static_Obj_List[i].empty())
				break;

			RENDERID eID = iter->Get_RenderID();
			m_RenderList[eID].push_back(iter);
		}
	}

	for (size_t i = 0; i < UI_OBJ_END; ++i)
	{
		for (auto& iter : m_UI_Obj_List[i])
		{
			iter->Late_Update();

			if (m_UI_Obj_List[i].empty())
				break;

			RENDERID eID = iter->Get_RenderID();

			if (eID != RENDER_SUPER)
				m_RenderList[eID].push_back(iter);
		}
	}

	for (size_t i = 0; i < DYNAMIC_OBJ_END; i++)
	{
		for (auto iter : m_Dynamic_Obj_List[i])
		{
			list<CObj*> listExceptMe = m_Dynamic_Obj_List[i];
			listExceptMe.remove(iter);
			CCollisionMgr::Collision_RectEx(iter, listExceptMe);
		}
	}
}

void CObjMgr::Render(HDC hDC)
{
	for (size_t i = 0; i < RENDER_END; ++i)
	{
		m_RenderList[i].sort([](CObj* pDst, CObj* pSrc)->bool
			{
				return pDst->Get_Info().fY < pSrc->Get_Info().fY;
			});

		for (auto& iter : m_RenderList[i])
			iter->Render(hDC);

		m_RenderList[i].clear();
	}
}

void CObjMgr::Release()
{
	for (size_t i = 0; i < DYNAMIC_OBJ_END; ++i)
	{
		for_each(m_Dynamic_Obj_List[i].begin(), m_Dynamic_Obj_List[i].end(), Safe_Delete<CObj*>);
		m_Dynamic_Obj_List[i].clear();
	}

	for (size_t i = 0; i < STATIC_OBJ_END; ++i)
	{
		for_each(m_Static_Obj_List[i].begin(), m_Static_Obj_List[i].end(), Safe_Delete<CObj*>);
		m_Static_Obj_List[i].clear();
	}

	for (size_t i = 0; i < UI_OBJ_END; ++i)
	{
		for_each(m_UI_Obj_List[i].begin(), m_UI_Obj_List[i].end(), Safe_Delete<CObj*>);
		m_UI_Obj_List[i].clear();
	}
}


void CObjMgr::Delete_ID_DynamicObj(DYNAMIC_OBJID eId)
{
	for (auto& iter : m_Dynamic_Obj_List[eId])
		Safe_Delete(iter);

	m_Dynamic_Obj_List[eId].clear();
}

void CObjMgr::Delete_ID_StaticObj(BUILDINGSTATE eId)
{
	for (auto& iter : m_Static_Obj_List[eId])
		Safe_Delete(iter);

	m_Static_Obj_List[eId].clear();
}

void CObjMgr::Delete_ID_UIObj(UI_OBJID eId)
{
	for (auto& iter : m_UI_Obj_List[eId])
		Safe_Delete(iter);

	m_UI_Obj_List[eId].clear();
}


CObj* CObjMgr::Get_Target(float _fX, float _fY)
{
	CObj* pTarget = nullptr;

	for (size_t i = 0; i < DYNAMIC_OBJ_END; i++)
	{
		for (auto iter : m_Dynamic_Obj_List[i])
		{
			RECT rect = iter->Get_Rect();
			if (rect.left <= _fX && rect.right >= _fX && rect.top <= _fY && rect.bottom >= _fY)
			{
				return iter;
			}
		}
	}

	return nullptr;
}

vector<CObj*> CObjMgr::Get_Targets(POINT _initPoint, POINT _goalPoint)
{
	vector<CObj*> vecDragObj;

	for (size_t i = 0; i < DYNAMIC_OBJ_END; i++)
	{
		for (auto iter : m_Dynamic_Obj_List[i])
		{
			INFO info = iter->Get_Info();

			if (info.fX >= _initPoint.x && info.fX <= _goalPoint.x && info.fY >= _initPoint.y && info.fY <= _goalPoint.y)
			{
				vecDragObj.push_back(iter);
			}
		}
	}

	return vecDragObj;
}
