#pragma once
#include "State.h"
class ICollectionState :
    public IState
{
public:
    ICollectionState();
    virtual ~ICollectionState();
public:
    void Initialize(CObj_Dynamic*) override;
    int Update(CObj_Dynamic*) override;
    void Late_Update(CObj_Dynamic*) override;
    void Render(CObj_Dynamic*, HDC hDC) override;
    void Release(CObj_Dynamic*) override;
    void Move_Frame(CObj_Dynamic*) override;
    virtual void Set_Astar(float, float, float, float) override;

};

