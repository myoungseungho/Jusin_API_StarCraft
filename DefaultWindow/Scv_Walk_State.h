#pragma once
#include "State.h"
class CScv_Walk_State :
    public IState
{
public:
    CScv_Walk_State();
    virtual ~CScv_Walk_State();
public:
    void Initialize(CObj*) override;
    int Update(CObj*) override;
    void Late_Update(CObj*) override;
    void Render(CObj*, HDC hDC) override;
    void Release(CObj*) override;
private:
    FRAME* m_pFrameCopy;
    TCHAR* m_pFrameKeyCopy;
};

