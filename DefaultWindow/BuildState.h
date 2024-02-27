#pragma once
#include "State.h"
class IBuildState :
    public IState
{
public:
    IBuildState();
    virtual ~IBuildState();
public:
    void Initialize(CObj_Dynamic*) override;
    int Update(CObj_Dynamic*) override;
    void Late_Update(CObj_Dynamic*) override;
    void Render(CObj_Dynamic*, HDC hDC) override;
    void Release(CObj_Dynamic*) override;
    void Move_Frame() override;
};

