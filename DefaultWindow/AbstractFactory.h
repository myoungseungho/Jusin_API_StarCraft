#pragma once

#include "Obj.h"
#include "Obj_Dynamic.h"
#include "Obj_UI.h"
#include "Obj_Static.h"
template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory(){}
	~CAbstractFactory(){}

public:
	static CObj*		Create()
	{
		CObj*		pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj*		Create(float _fX, float _fY)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);

		return pObj;
	}

	static CObj*		Create(float _fX, float _fY, float _fAngle)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);

		return pObj;
	}

	static CObj_Dynamic* Create_Dynamic()
	{
		CObj_Dynamic* pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj_Dynamic* Create_Dynamic(float _fX, float _fY)
	{
		CObj_Dynamic* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);

		return pObj;
	}

	static CObj_Dynamic* Create_Dynamic(float _fX, float _fY, float _fAngle)
	{
		CObj_Dynamic* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);

		return pObj;
	}

	static CObj_UI* Create_UI()
	{
		CObj_UI* pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj_UI* Create_UI(float _fX, float _fY)
	{
		CObj_UI* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);

		return pObj;
	}

	static CObj_UI* Create_UI(float _fX, float _fY, float _fAngle)
	{
		CObj_UI* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);

		return pObj;
	}

	static CObj_Static* Create_Static()
	{
		CObj_Static* pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj_Static* Create_Static(float _fX, float _fY)
	{
		CObj_Static* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		return pObj;
	}

	static CObj_Static* Create_Static(float _fX, float _fY, float _fAngle)
	{
		CObj_Static* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);

		return pObj;
	}
};

