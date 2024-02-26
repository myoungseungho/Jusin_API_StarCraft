#pragma once
#include "Obj.h"
class CObj_UI :
    public CObj
{
public:
    CObj_UI();
    virtual ~CObj_UI();
public:
	void Initialize() PURE;
	int Update() PURE;
	void Late_Update()PURE;
	virtual void Render(HDC hDC);
	void Release() PURE;

    void		Move_Frame();
	HDC			Get_HDC();
};

