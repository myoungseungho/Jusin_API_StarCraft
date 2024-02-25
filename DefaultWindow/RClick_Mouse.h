#pragma once
#include "Command.h"
class CRClick_Mouse :
    public CCommand
{
public:
    CRClick_Mouse();
    virtual ~CRClick_Mouse();
public:
    void Initialize() override;
    void Execute() override { RClick(); };
private:
    void RClick();

};

