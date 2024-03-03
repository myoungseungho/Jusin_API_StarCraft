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

	virtual UIOBJECTTYPE GetType() const PURE;
	virtual int GetDetailType() const PURE; // 모든 UI 오브젝트는 상태를 반환하는 메서드를 가져야 함.
	void		Move_Frame();
	HDC			Get_HDC();

	virtual void		Set_Dead()
	{
		if (this->GetType() == UI_OBJECT_ICON)
		{
			int i = 3;
		}
		m_bDead = true;
	}

protected:
	int			m_iDrawID;
	int			m_iOption;
};

