#include "stdafx.h"
#include "Scv.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Scv_Idle_State.h"
#include "Scv_Walk_State.h"
#include "Scv_Attack_State.h"
#include "StateMgr.h"
//���� ��ü �����ÿ��� BmpFile ���
CScv::CScv()
{
	InsertBmpFile();
}

//���� �����ÿ��� BmpFile ������� ����
CScv::CScv(const CScv& other)
{

}

CScv::~CScv()
{
	Release();
}

void CScv::Initialize()
{
	IState* IdleState = CStateMgr::Get_Instance()->GetVecObjState(OBJ_SCV)[SCV_ATTACK];
	ChangeState(IdleState);

	m_eRender = RENDER_GAMEOBJECT;

	//ó�� ũ�� ����
	m_tInfo.fCX = 72.f;
	m_tInfo.fCY = 72.f;
}

int CScv::Update()
{
	__super::Update_Rect();

	m_CurrentState->Update(this);
	return 0;
}

void CScv::Late_Update()
{
	m_CurrentState->Late_Update(this);

	__super::Move_Frame();
}

void CScv::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		m_tRect.left + iScrollX, // ���� ���� ��ġ ��ǥ
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,	// ���� ���� �̹����� ����, ����
		(int)m_tInfo.fCY,
		hMemDC,		// ��Ʈ���� ������ �ִ� DC
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,	// ����� ��Ʈ�� ����
		(int)m_tInfo.fCY,	// ����� ��Ʈ�� ����
		RGB(0, 0, 0));	// ������ ���� ��

	/*m_CurrentState->Render(this,hDC);*/
}

void CScv::Release()
{
	m_CurrentState->Release(this);
}

void CScv::ChangeState(IState* _newState)
{
	if (m_CurrentState)
	{
		/*m_CurrentState->Release(this);
		Safe_Delete(m_CurrentState);*/
	}

	m_CurrentState = _newState;
	m_CurrentState->Initialize(this);
}

void CScv::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Scv/Idle/SCV_IDLE.bmp", L"SCV_IDLE");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Scv/Attack/SCV_ATTACK.bmp", L"SCV_ATTACK");
	/*Set_FrameKey(L"SCV_IDLE");
	Set_FrameKey(L"SCV_ATTACK");*/
}
