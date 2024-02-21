#pragma once
#include "Obj.h"
#include "Obj_Dynamic.h"
class CScrewBullet :	public CObj_Dynamic
{
public:
	CScrewBullet();
	virtual ~CScrewBullet();

public:
	virtual void Initialize() override;
	virtual int  Update() override;
	virtual void Late_Update()override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	POINT		m_tCenter;

	float		m_fRotAngle;
	float		m_fRotSpeed;
	bool		m_bStart;
};

