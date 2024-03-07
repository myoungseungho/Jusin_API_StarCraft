#pragma once
#include "Obj_UI.h"
class CUI_NuclearSilo_Wire :
    public CObj_UI
{
public:
	CUI_NuclearSilo_Wire();
	virtual ~CUI_NuclearSilo_Wire();
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	virtual void Render(HDC hDC) override;
	void Release() override;
	UIOBJECTTYPE GetType() const override;
	int GetDetailType() const override;
protected:
	virtual void InsertBmpFile() override;
};
