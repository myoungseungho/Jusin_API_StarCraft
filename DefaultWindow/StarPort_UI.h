#pragma once
#include "Obj_UI.h"
class CStarPort_UI :
    public CObj_UI
{
public:
    CStarPort_UI();
    virtual ~CStarPort_UI();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Release() override;
    ICONSTATE GetType() const override;
};

