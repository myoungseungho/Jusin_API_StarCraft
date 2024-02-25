#include "stdafx.h"
#include "Scv_Walk_State.h"
#include "TileMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
CScv_Walk_State::CScv_Walk_State() : m_dwTime(0)
{
}

CScv_Walk_State::~CScv_Walk_State()
{
}

void CScv_Walk_State::Initialize(CObj_Dynamic* _scv)
{
	m_pFrameCopy = _scv->Get_Frame();
	m_pFrameKeyCopy = _scv->Get_FrameKey();

	*m_pFrameKeyCopy = L"SCV_IDLE";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 16;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 200;
	m_pFrameCopy->dwTime = GetTickCount();

	POINT scvPoint = _scv->GetMousePT();
	INFO info = _scv->Get_Info();

	int ScvX = info.fX / TILECX;
	int ScvY = info.fY / TILECY;

	int	TileX = scvPoint.x / TILECX;
	int	TileY = scvPoint.y / TILECY;

	IWalkState::Set_Astar(ScvX, ScvY, TileX, TileY);

	m_listPathTile = CTileMgr::Get_Instance()->GetListPath(m_Path);
}

int CScv_Walk_State::Update(CObj_Dynamic* _scv)
{
	Move(_scv);
	return 0;
}

void CScv_Walk_State::Late_Update(CObj_Dynamic*)
{
}

void CScv_Walk_State::Render(CObj_Dynamic* _scv, HDC hDC)
{
	
}

void CScv_Walk_State::Release(CObj_Dynamic*)
{
}

void CScv_Walk_State::Move_Frame()
{
}

void CScv_Walk_State::Move(CObj_Dynamic* _scv)
{
	// 현재 목표 타일이 없거나 경로를 모두 완료한 경우
	if (m_listPathTile.empty()) {
		return; // 이동 중지
	}

	// 현재 목표 타일
	CObj* currentTargetTile = m_listPathTile.front();
	dynamic_cast<CTile*>(currentTargetTile)->Set_Value(1, 0);

	// 현재 목표 타일의 중심 좌표 계산
	float targetX = currentTargetTile->Get_Info().fX;
	float targetY = currentTargetTile->Get_Info().fY;

	// SCV의 현재 위치
	float scvX = _scv->Get_Info().fX;
	float scvY = _scv->Get_Info().fY;

	// 이동해야 할 방향 벡터 계산
	float dirX = targetX - scvX;
	float dirY = targetY - scvY;
	float length = sqrt(dirX * dirX + dirY * dirY);

	// 단위 방향 벡터와 속도를 사용하여 이동
	float speed = 5.0f; // 적당한 속도 값
	if (length > speed) { // 목표까지의 거리가 속도보다 클 경우, 이동 실행
		dirX = (dirX / length) * speed;
		dirY = (dirY / length) * speed;
		_scv->Set_PosX(dirX);
		_scv->Set_PosY(dirY);
	}
	else {
		// 목표 타일에 도달했거나 매우 가까운 경우, 목표 타일을 다음 타일로 변경
		m_listPathTile.pop_front();
		if (!m_listPathTile.empty()) {
			// 다음 타일로 이동을 계속합니다.
			Move(_scv);
		}
	}
}
