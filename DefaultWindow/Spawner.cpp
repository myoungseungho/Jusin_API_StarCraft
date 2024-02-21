#include "stdafx.h"
#include "Spawner.h"

CSpawner::CSpawner(CObj* prototype) : m_Prototype(prototype)
{

}

CSpawner::~CSpawner()
{
}


CObj* CSpawner::SpawnCObj(float _fX, float _fY)
{
	return m_Prototype->Clone(_fX, _fY);
}
