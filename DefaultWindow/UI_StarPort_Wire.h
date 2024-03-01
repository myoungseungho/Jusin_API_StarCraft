#pragma once
#include "Obj_UI.h"
class CUI_StarPort_Wire :
    public CObj_UI
{
public:
	CUI_StarPort_Wire();
	virtual ~CUI_StarPort_Wire();
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
