#pragma once
#include "Obj.h"
class CObj_UI :
    public CObj
{
public:
    CObj_UI();
    virtual ~CObj_UI();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void		Move_Frame();

};

