#pragma once
#include "Obj.h"
class CObj_UI :
    public CObj
{
public:
    CObj_UI();
    virtual ~CObj_UI();
public:
	void Initialize() PURE;
	int Update() PURE;
	void Late_Update()PURE;
	virtual void Render(HDC hDC);
	void Release() PURE;
	void UpdateMouse();
	void SetDrawID(int _drawId) { m_iDrawID = _drawId; };

	virtual ICONSTATE GetType() const PURE;

    void		Move_Frame();
	HDC			Get_HDC();

protected:
	int			m_iDrawID;
	int			m_iOption;
};

