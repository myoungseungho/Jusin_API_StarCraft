#pragma once
#include "Obj_Dynamic.h"
#include "State.h"
class CScv : public CObj_Dynamic
{
public:
	CScv();
	virtual ~CScv();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

	void Set_Astar(float _fX, float _fY, float _goalX, float _goalY);
protected:
	virtual void InsertBmpFile() override;

private:
	void Move();
	vector<CObj*> m_vecPathTile;
	vector<pair<int, int>> m_Path;

private:
	DWORD m_dwTime;

	DYNAMIC_OBJID GetType() const override;
};

