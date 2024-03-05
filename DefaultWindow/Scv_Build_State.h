#pragma once
#include "BuildState.h"
#include "Obj_Static.h"
class CScv_Build_State :
    public IBuildState
{
public:
    CScv_Build_State();
    virtual ~CScv_Build_State();
public:
    void Initialize(CObj_Dynamic*) override;
    int Update(CObj_Dynamic*) override;
    void Late_Update(CObj_Dynamic*) override;
    void Render(CObj_Dynamic*, HDC hDC) override;
    void Release(CObj_Dynamic*) override;
private:
    void BuildStart(CObj_Dynamic* _scv);
    void SCV_Build_Move(CObj_Dynamic* _scv);
private:
    bool m_build_Start;
    vector<CObj_Static*> m_vecTest;
    CObj_Static* m_Building;
};

