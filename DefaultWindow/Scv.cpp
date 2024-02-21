#include "stdafx.h"
#include "Scv.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Scv_Idle_State.h"
#include "Scv_Walk_State.h"
#include "StateMgr.h"
//원본 객체 생성시에만 BmpFile 등록
CScv::CScv() : m_CurrentState(nullptr)
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
	IState* IdleState = CStateMgr::Get_Instance()->GetVecObjState(OBJ_SCV)[SCV_IDLE];
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
}

void CScv::Render(HDC hDC)
{
	m_CurrentState->Render(this,hDC);
}

void CScv::Release()
{
	m_CurrentState->Release(this);
}

void CScv::ChangeState(IState* _newState)
{
	if (m_CurrentState)
	{
		m_CurrentState->Release(this);
		Safe_Delete(m_CurrentState);
	}

	m_CurrentState = _newState;
	m_CurrentState->Initialize(this);
}

void CScv::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Scv/Idle/SCV_IDLE.bmp", L"SCV_IDLE");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Scv/Attack/SCV_ATTACK.bmp", L"SCV_ATTACK");
}
