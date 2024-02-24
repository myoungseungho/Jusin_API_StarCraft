#pragma once
#include "Obj_Dynamic.h"
class CMedic :
    public CObj_Dynamic
{
public:
	CMedic();
	virtual ~CMedic();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

protected:
	virtual void InsertBmpFile() override;

	// CObj_Dynamic��(��) ���� ��ӵ�
	DYNAMIC_OBJID GetType() const override;
};

