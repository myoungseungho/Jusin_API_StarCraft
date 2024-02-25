#pragma once
#include "Command.h"

class Drag_LMouse_Long :
    public CCommand
{
public:
    Drag_LMouse_Long();
    virtual ~Drag_LMouse_Long();
public:
    void Initialize() override;
    void Initialize(POINT) override;
    void Execute() override { DragLClick(); };
private:
    void DragLClick();
private:
    POINT m_InitPoint;
};
