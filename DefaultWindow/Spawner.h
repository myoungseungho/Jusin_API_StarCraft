#pragma once
#include "Obj.h"
class CSpawner
{
public:
	CSpawner(CObj* prototype);
	~CSpawner();
public:
	CObj* SpawnCObj(float _fX, float _fY);
private:
	CObj* m_Prototype;
};

