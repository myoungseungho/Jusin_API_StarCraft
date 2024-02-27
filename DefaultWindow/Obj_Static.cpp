#include "stdafx.h"
#include "Obj_Static.h"
#include "TileMgr.h"
CObj_Static::CObj_Static() : m_IsInfoUpdate(false), m_UIBuilding(false)
{
}

CObj_Static::~CObj_Static()
{
}

void CObj_Static::SetObstcale()
{
	list<CObj*> staticTileList = CTileMgr::Get_Instance()->GetStaticTile(this);

	for (auto iter : staticTileList)
	{
		CTile* iterTile = dynamic_cast<CTile*>(iter);

		if (iterTile != nullptr)
		{
			iterTile->Set_Value(1, 0);
		}
	}

	CTileMgr::Get_Instance()->SetVecObstcales(staticTileList);
}

