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
    void Render(HDC _hdc);
    void Execute() override { DragLClick(); };
private:
    void DragLClick();
    void UpdatePT();
private:
    POINT m_InitPoint;
    POINT m_CurrentPoint;

    // CCommand을(를) 통해 상속됨
    void Release() override;
};

