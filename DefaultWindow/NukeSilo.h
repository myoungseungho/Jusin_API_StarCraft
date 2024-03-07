#pragma once
#include "Obj_Static.h"
class CNukeSilo :
    public CObj_Static
{
public:
	CNukeSilo();
	virtual ~CNukeSilo();
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
public:
	virtual void Spawn_Unit(DYNAMIC_OBJID);
protected:
	virtual void InsertBmpFile() override;

	// CObj_Static��(��) ���� ��ӵ�
	BUILDINGSTATE GetType() const override;
private:
	bool m_CompleteAddon;
};
