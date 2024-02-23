#include "stdafx.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"

CObjMgr*	CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}

CObjMgr::~CObjMgr()
{
	Release();
}

//void CObjMgr::Add_Object(OBJID eID, CObj* pObj)
//{
//	if (OBJ_END <= eID || nullptr == pObj)
//		return;
//
//	m_ObjList[eID].push_back(pObj);
//}

void CObjMgr::Add_Dynamic_Object(DYNAMIC_OBJID eID, CObj_Dynamic * pObj)
{
	if (DYNAMIC_OBJ_END <= eID || nullptr == pObj)
		return;

	m_Dynamic_Obj_List[eID].push_back(pObj);
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
				Safe_Delete<CObj_Dynamic*>(*iter);
				iter = m_Dynamic_Obj_List[i].erase(iter);
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
			m_Dynamic_RenderList[eID].push_back(iter);
		}
	}
}

void CObjMgr::Render(HDC hDC)
{
	for (size_t i = 0; i < RENDER_END; ++i)
	{
		m_Dynamic_RenderList[i].sort([](CObj_Dynamic* pDst, CObj_Dynamic* pSrc)->bool
			{
				return pDst->Get_Info().fY < pSrc->Get_Info().fY;
			});

		for (auto& iter : m_Dynamic_RenderList[i])
			iter->Render(hDC);

		m_Dynamic_RenderList[i].clear();
	}
}

void CObjMgr::Release()
{

	for (size_t i = 0; i < DYNAMIC_OBJ_END; ++i)
	{
		for_each(m_Dynamic_Obj_List[i].begin(), m_Dynamic_Obj_List[i].end(), Safe_Delete<CObj_Dynamic*>);
		m_Dynamic_Obj_List[i].clear();
	}
}


void CObjMgr::Delete_ID_DynamicObj(DYNAMIC_OBJID eId)
{
	for (auto& iter : m_Dynamic_Obj_List[eId])
		Safe_Delete(iter);

	m_Dynamic_Obj_List[eId].clear();
}

CObj * CObjMgr::Get_Target(DYNAMIC_OBJID eID, CObj_Dynamic* pObj)
{
	if (m_Dynamic_Obj_List[eID].empty())
		return nullptr;

	CObj*	pTarget = nullptr;
	float	fDistance(0.f);

	for (auto& iter : m_Dynamic_Obj_List[eID])
	{
		if(iter->Get_Dead())
			continue;

		float	fWidth = abs(pObj->Get_Info().fX - iter->Get_Info().fX);
		float	fHeight = abs(pObj->Get_Info().fY - iter->Get_Info().fY);

		float	fDiagonal = sqrt(fWidth * fWidth + fHeight * fHeight);

		if ((!pTarget) || (fDistance > fDiagonal))
		{
			pTarget = iter;
			fDistance = fDiagonal;
		}
	}
	
	return pTarget;
}
