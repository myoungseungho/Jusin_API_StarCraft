#include "stdafx.h"
#include "Scv.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Scv_Idle_State.h"
#include "Scv_Walk_State.h"
#include "Scv_Attack_State.h"
#include "StateMgr.h"
//원본 객체 생성시에만 BmpFile 등록
CScv::CScv()
{
	InsertBmpFile();
}

//복사 생성시에는 BmpFile 등록하지 않음
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

	//처음 크기 고정
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
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		m_tRect.left + iScrollX, // 복사 받을 위치 좌표
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,	// 복사 받을 이미지의 가로, 세로
		(int)m_tInfo.fCY,
		hMemDC,		// 비트맵을 가지고 있는 DC
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,			// 비트맵 출력 시작 좌표 LEFT, TOP
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,	// 출력할 비트맵 가로
		(int)m_tInfo.fCY,	// 출력할 비트맵 세로
		RGB(0, 0, 0));	// 제거할 색상 값

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
