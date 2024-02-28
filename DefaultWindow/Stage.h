#pragma once
#include "Scene.h"
#include "Obj_UI.h"
class CStage :
	public CScene
{
public:
	CStage();
	virtual ~CStage();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:
	void Init_Obj_Spawn();
	void Static_Obj_Spawn();
	void Ally_Obj_Spawn();
	void Enemy_Obj_Spawn();
};

