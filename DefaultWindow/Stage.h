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

	void Enemy_Dynamic_Obj_Spawn();
private:
	void Init_Bmp();
private:
	void Init_Obj_Spawn();
	void Ally_Static_Obj_Spawn();
	void Enemy_Static_Obj_Spawn();
	void Ally_Dynamic_Obj_Spawn();
};

