#pragma once
#include "CollectionState.h"
class CScv_Collection_State :
    public ICollectionState
{
public:
    CScv_Collection_State();
    virtual ~CScv_Collection_State();
public:
    void Initialize(CObj_Dynamic*) override;
    int Update(CObj_Dynamic*) override;
    void Late_Update(CObj_Dynamic*) override;
    void Render(CObj_Dynamic*, HDC hDC) override;
    void Release(CObj_Dynamic*) override;
private:
    void Collection(CObj_Dynamic*);
    void CenterMove(CObj_Dynamic*);
private:
    bool m_bCollisionCenter;
    bool m_bCollisionMineral;
    bool m_bGetMineral;
    int    m_AttackFileSize;
    int    m_Offset_Attack;
    DWORD m_CurrentTime;
    CObj* m_targetMineral;
};

