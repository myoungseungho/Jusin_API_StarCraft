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
	void Render(HDC hDC) PURE;
	void Release() PURE;

    void		Move_Frame();
	void		Set_UI();
	HDC			Get_HDC();
};

