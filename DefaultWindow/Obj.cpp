#include "stdafx.h"
#include "Obj.h"
#include "BmpMgr.h"

CObj::CObj() :m_eDir(DIR_END), m_fAngle(0.f), m_pTarget(nullptr), m_pFrameKey(nullptr), m_eRender(RENDER_END), m_Faction(FACTION_NON), m_bDead(false), m_Collision(COLLISION_OK), m_bCliecked(false), m_pFrameDisplayKey(nullptr)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_Stat, sizeof(STAT));
	InsertBmpFile();
}

CObj::~CObj()
{
}


void CObj::Update_Rect()
{
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}


void CObj::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Small_Hp.bmp", L"Small_Hp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mid_Hp.bmp", L"Mid_Hp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Big_Hp.bmp", L"Big_Hp");
}
