#include "stdafx.h"
#include "FireBat_Attack_State.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CFireBat_Attack_State::CFireBat_Attack_State()
{
}

CFireBat_Attack_State::~CFireBat_Attack_State()
{
}

void CFireBat_Attack_State::Initialize(CObj_Dynamic* _fireBat)
{
	m_pFrameCopy = _fireBat->Get_Frame();
	m_pFrameKeyCopy = _fireBat->Get_FrameKey();

	*m_pFrameKeyCopy = L"Firebat_Attack_Right_90";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 0;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 200;
	m_pFrameCopy->dwTime = GetTickCount();

	m_pFrameKey_Attack = L" FireBat_Bullet_Right";
	m_tFrame_Attack.iFrameStart = 0;
	m_tFrame_Attack.iFrameEnd = 11;
	m_tFrame_Attack.iMotion = 0;
	m_tFrame_Attack.dwSpeed = 50;
	m_tFrame_Attack.dwTime = GetTickCount();
}

int CFireBat_Attack_State::Update(CObj_Dynamic*)
{
	return 0;
}

void CFireBat_Attack_State::Late_Update(CObj_Dynamic*)
{
}

void CFireBat_Attack_State::Render(CObj_Dynamic* _fireBat, HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey_Attack);

	GdiTransparentBlt(
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		_fireBat->Get_Rect().left + iScrollX, // ���� ���� ��ġ ��ǥ
		_fireBat->Get_Rect().top + iScrollY,
		(int)_fireBat->Get_Info().fCX,	// ���� ���� �̹����� ����, ����
		(int)_fireBat->Get_Info().fCY,
		hMemDC,		// ��Ʈ���� ������ �ִ� DC
		(int)_fireBat->Get_Info().fCX * m_tFrame_Attack.iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		(int)_fireBat->Get_Info().fCY * m_tFrame_Attack.iMotion,
		(int)_fireBat->Get_Info().fCX,	// ����� ��Ʈ�� ����
		(int)_fireBat->Get_Info().fCY,	// ����� ��Ʈ�� ����
		RGB(0, 0, 0));	// ������ ���� ��
}

void CFireBat_Attack_State::Release(CObj_Dynamic*)
{
}