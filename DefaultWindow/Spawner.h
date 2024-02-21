#pragma once
#include "Obj_Dynamic.h"
class CSpawner
{
public:
	CSpawner(CObj_Dynamic* prototype);
	~CSpawner();
public:
	CObj_Dynamic* SpawnCObj(float _fX, float _fY);
private:
	CObj_Dynamic* m_Prototype;
};

