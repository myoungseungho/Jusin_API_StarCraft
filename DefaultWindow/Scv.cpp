#include "stdafx.h"
#include "Scv.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Scv_Idle_State.h"
#include "Scv_Walk_State.h"
#include "Scv_Attack_State.h"
#include "Scv_Die_State.h"
#include "Tile.h"
#include "AStarMgr.h"
#include "TileMgr.h"
CScv::CScv() : m_dwTime(0)
{
	InsertBmpFile();
}

CScv::~CScv()
{
	Release();
}

void CScv::Initialize()
{
	if (m_CurrentState == NON_STATE)
	{
		m_eRender = RENDER_GAMEOBJECT;

		//처음 크기 고정
		m_tInfo.fCX = 72.f;
		m_tInfo.fCY = 72.f;

		m_vecState.push_back(new CScv_Idle_State);
		m_vecState.push_back(new CScv_Walk_State);
		m_vecState.push_back(new CScv_Attack_State);
		m_vecState.push_back(new CScv_Die_State);

		ChangeState(IDLE_STATE);
	}
	else
	{
		int ScvX = m_tInfo.fX / TILECX;
		int ScvY = m_tInfo.fY / TILECY;

		int	TileX = m_MousePT.x / TILECX;
		int	TileY = m_MousePT.y / TILECY;

		Set_Astar(ScvX, ScvY, TileX, TileY);
		m_vecPathTile = CTileMgr::Get_Instance()->GetVecPath(m_Path);
	}
}

int CScv::Update()
{
	m_vecState[m_CurrentState]->Update(this);
	Move();


	__super::Update_Rect();

	/*if (GetAsyncKeyState(VK_RIGHT))
	{
		__super::Set_PosX(3.f);
	}*/

//#ifdef _DEBUG
//
//	if (m_dwTime + 1000 < GetTickCount())
//	{
//		system("cls");
//		cout << "Left : " << m_tRect.left << endl;
//		cout << "Right : " << m_tRect.right << endl;
//		cout << "Top : " << m_tRect.top << endl;
//		cout << "Bottom : " << m_tRect.bottom << endl;
//		cout << "X : " << m_tInfo.fX << endl;
//		cout << "Y : " << m_tInfo.fY << endl;
//		m_dwTime = GetTickCount();
//	}
//#endif


	return OBJ_NOEVENT;
}

void CScv::Late_Update()
{
	m_vecState[m_CurrentState]->Late_Update(this);

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

	m_vecState[m_CurrentState]->Render(this, hDC);
}

void CScv::Release()
{
	m_vecState[m_CurrentState]->Release(this);
}



void CScv::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Scv/Idle/SCV_IDLE.bmp", L"SCV_IDLE");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Scv/Attack/SCV_ATTACK.bmp", L"SCV_ATTACK");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/ScvAtt/SCV_Bullet.bmp", L"SCV_Bullet");
}

void CScv::Move()
{
	// 현재 목표 타일이 없거나 경로를 모두 완료한 경우
	if (m_vecPathTile.empty()) {
		return; // 이동 중지
	}

	// 현재 목표 타일
	CObj* currentTargetTile = m_vecPathTile.front();
	dynamic_cast<CTile*>(currentTargetTile)->Set_Value(1, 0);

	// 현재 목표 타일의 중심 좌표 계산
	float targetX = currentTargetTile->Get_Info().fX;
	float targetY = currentTargetTile->Get_Info().fY;

	// SCV의 현재 위치
	float scvX = m_tInfo.fX;
	float scvY = m_tInfo.fY;

	// 이동해야 할 방향 벡터 계산
	float dirX = targetX - scvX;
	float dirY = targetY - scvY;
	float length = sqrt(dirX * dirX + dirY * dirY);

	// 단위 방향 벡터와 속도를 사용하여 이동
	float speed = 5.0f; // 적당한 속도 값
	if (length > speed) { // 목표까지의 거리가 속도보다 클 경우, 이동 실행
		dirX = (dirX / length) * speed;
		dirY = (dirY / length) * speed;
		Set_PosX(dirX);
		Set_PosY(dirY);
	}
	else {
		// 목표 타일에 도달했거나 매우 가까운 경우, 목표 타일을 다음 타일로 변경
		m_vecPathTile.erase(m_vecPathTile.begin()); // 현재 목표 타일 제거
		if (!m_vecPathTile.empty()) {
			// 다음 타일로 이동을 계속합니다.
			Move();
		}
	}
}

void CScv::Set_Astar(float _fX, float _fY, float _goalX, float _goalY)
{
	pair<int, int> start(_fX, _fY);
	pair<int, int> goal(_goalX, _goalY);

	m_Path = CAStarMgr::Get_Instance()->AStarSearch(start, goal);
}

DYNAMIC_OBJID CScv::GetType() const
{
	return DYANMIC_OBJ_SCV;
}
