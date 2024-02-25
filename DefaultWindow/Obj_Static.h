#pragma once
#include "Obj.h"
class CObj_Static :
    public CObj
{
public:
    CObj_Static();
    virtual ~CObj_Static();
public:
    virtual void Initialize();
    int Update() PURE;
    void Late_Update()PURE;
    void Render(HDC hDC) PURE;
    void Release() PURE;

    bool m_IsInfoUpdate;
};

