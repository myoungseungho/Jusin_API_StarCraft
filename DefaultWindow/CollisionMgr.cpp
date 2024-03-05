#include "stdafx.h"
#include "CollisionMgr.h"
#include "ScrollMgr.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Rect(list<CObj_Dynamic*> _Dst, list<CObj_Dynamic*> _Src)
{
	RECT	rc{};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &(Dst->Get_Rect()), &(Src->Get_Rect())))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}

}

bool CCollisionMgr::Check_Sphere(CObj_Dynamic* pDst, CObj_Dynamic* pSrc)
{
	float	fWidth = abs(pDst->Get_Info().fX - pSrc->Get_Info().fX);
	float	fHeight = abs(pDst->Get_Info().fY - pSrc->Get_Info().fY);

	float	fDiagonal = sqrt(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (pDst->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;

	return fRadius >= fDiagonal;
}

void CCollisionMgr::Collision_Sphere(list<CObj_Dynamic*> _Dst, list<CObj_Dynamic*> _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Sphere(Dst, Src))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

bool CCollisionMgr::Check_Rect(float* pX, float* pY, CObj* pDst, CObj* pSrc)
{
	float		fDistance_W = abs(pDst->Get_Info().fX - pSrc->Get_Info().fX);
	float		fDistance_H = abs(pDst->Get_Info().fY - pSrc->Get_Info().fY);

	float		fRadiusX = (pDst->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.2f;
	float		fRadiusY = (pDst->Get_Info().fCY + pSrc->Get_Info().fCY) * 0.2f;

	if ((fRadiusX >= fDistance_W) && (fRadiusY >= fDistance_H))
	{
		*pX = fRadiusX - fDistance_W;
		*pY = fRadiusY - fDistance_H;

		return true;
	}

	return false;
}

void CCollisionMgr::Collision_RectEx(list<CObj*> _Dst, list<CObj*> _Src)
{
	float	fX(0.f), fY(0.f);
	float fInterpolation = 0.1f;
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			//Idle상태일 때만 충돌체크
			CObj_Dynamic* DstDynamicObj = dynamic_cast<CObj_Dynamic*>(Dst);
			CObj_Dynamic* SrcDynamicObj = dynamic_cast<CObj_Dynamic*>(Src);

			//Attack_State에서 Move하는 도중에는 충돌 처리 안되다가 Move 안할때는 어떤 State에서라도 충돌처리 되게 끔 바꾸자.
			if (Dst == Src || DstDynamicObj->GetStateID() == WALK_STATE || SrcDynamicObj->GetStateID() == WALK_STATE || DstDynamicObj->GetAttackRun() || SrcDynamicObj->GetAttackRun())
				continue;

			if (Check_Rect(&fX, &fY, Dst, Src))
			{
				Dst->Set_CollisionState(COLLISION_OK);
				Src->Set_CollisionState(COLLISION_OK);
				// 상하 충돌
				if (fX > fY)
				{
					// 상 충돌
					if (Dst->Get_Info().fY < Src->Get_Info().fY)
					{
						//시작점
						float start = Dst->Get_Info().fY;
						//종착지
						float Destination = Dst->Get_Info().fY - fY;

						float newY = start + (Destination - start) * fInterpolation;
						Dst->Set_PosY(newY - start);
					}

					// 하 충돌
					else
					{
						//시작점
						float start = Dst->Get_Info().fY;
						//종착지
						float Destination = Dst->Get_Info().fY + fY;

						float newY = start + (Destination - start) * fInterpolation;
						Dst->Set_PosY(newY - start);
					}
				}

				// 좌우 충돌
				else
				{
					// 좌 충돌
					if (Dst->Get_Info().fX < Src->Get_Info().fX)
					{
						//시작점
						float start = Dst->Get_Info().fX;
						//종착지
						float Destination = Dst->Get_Info().fX - fX;

						float newX = start + (Destination - start) * fInterpolation;
						Dst->Set_PosX(newX - start);
					}

					// 우 충돌
					else
					{
						//시작점
						float start = Dst->Get_Info().fX;
						//종착지
						float Destination = Dst->Get_Info().fX + fX;

						float newX = start + (Destination - start) * fInterpolation;
						Dst->Set_PosX(newX - start);
					}
				}
			}
			else
			{
				Dst->Set_CollisionState(COLLISION_NOT);
				Src->Set_CollisionState(COLLISION_NOT);
			}
		}
	}
}

void CCollisionMgr::Collision_RectEx(CObj* _Dst, list<CObj*> _Src)
{
	float	fX(0.f), fY(0.f);

	for (auto& Src : _Src)
	{
		if (Check_Rect(&fX, &fY, _Dst, Src))
		{
			// 상하 충돌
			if (fX > fY)
			{
				// 상 충돌
				if (_Dst->Get_Info().fY < Src->Get_Info().fY)
				{
					_Dst->Set_PosY(-fY);
				}

				// 하 충돌
				else
				{
					_Dst->Set_PosY(fY);
				}
			}

			// 좌우 충돌
			else
			{
				// 좌 충돌
				if (_Dst->Get_Info().fX < Src->Get_Info().fX)
				{
					_Dst->Set_PosX(-fX);
				}

				// 우 충돌
				else
				{
					_Dst->Set_PosX(fX);
				}
			}
		}
	}
}
