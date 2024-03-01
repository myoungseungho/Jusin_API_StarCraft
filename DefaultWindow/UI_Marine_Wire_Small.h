#pragma once
#include "Obj_UI.h"
class CUI_Marine_Wire_Small :
    public CObj_UI
{
public:
	CUI_Marine_Wire_Small();
	virtual ~CUI_Marine_Wire_Small();
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

