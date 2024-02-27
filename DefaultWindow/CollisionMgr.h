#pragma once

#include "Define.h"
#include "Obj_Dynamic.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void	Collision_Rect(list<CObj_Dynamic*> _Dst, list<CObj_Dynamic*> _Src);

	static bool Check_Sphere(CObj_Dynamic* pDst, CObj_Dynamic* pSrc);
	static void	Collision_Sphere(list<CObj_Dynamic*> _Dst, list<CObj_Dynamic*> _Src);

	static bool Check_Rect(float* pX, float* pY, CObj* pDst, CObj* pSrc);
	static void Collision_RectEx(CObj* _Dst, list<CObj*> _Src);
	static void	Collision_RectEx(list<CObj*> _Dst, list<CObj*> _Src);
};

