#pragma once
#include "Obj.h"
class CUI_Text_Mgr
{
public:
	CUI_Text_Mgr();
	~CUI_Text_Mgr();
public:
	void Initialize();
	void Render(HDC);
public:
	void OnClickObj(CObj*);
	void SetClear_Text();
private:
	CObj* m_ClieckObj;
};

