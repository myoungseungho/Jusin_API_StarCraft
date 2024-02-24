#pragma once
#include "State.h"
class IWalkState :
	public IState
{
public:
	IWalkState();
	virtual ~IWalkState();
public:
	void Set_Astar(float, float, float, float);
	vector<pair<int, int>> m_Path;

public:
	void Initialize(CObj_Dynamic*) override;
	int Update(CObj_Dynamic*) override;
	void Late_Update(CObj_Dynamic*) override;
	void Render(CObj_Dynamic*, HDC hDC) override;
	void Release(CObj_Dynamic*) override;
	void Move_Frame() override;

protected:
	vector<CObj*> m_vecPathTile;
};

