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
	// ���� ��ǥ Ÿ���� ���ų� ��θ� ��� �Ϸ��� ���
	if (m_listPathTile.empty()) {
		return; // �̵� ����
	}

	// ���� ��ǥ Ÿ��
	CObj* currentTargetTile = m_listPathTile.front();
	dynamic_cast<CTile*>(currentTargetTile)->Set_Value(1, 0);

	// ���� ��ǥ Ÿ���� �߽� ��ǥ ���
	float targetX = currentTargetTile->Get_Info().fX;
	float targetY = currentTargetTile->Get_Info().fY;

	// SCV�� ���� ��ġ
	float scvX = _scv->Get_Info().fX;
	float scvY = _scv->Get_Info().fY;

	// �̵��ؾ� �� ���� ���� ���
	float dirX = targetX - scvX;
	float dirY = targetY - scvY;
	float length = sqrt(dirX * dirX + dirY * dirY);

	// ���� ���� ���Ϳ� �ӵ��� ����Ͽ� �̵�
	float speed = 5.0f; // ������ �ӵ� ��
	if (length > speed) { // ��ǥ������ �Ÿ��� �ӵ����� Ŭ ���, �̵� ����
		dirX = (dirX / length) * speed;
		dirY = (dirY / length) * speed;
		_scv->Set_PosX(dirX);
		_scv->Set_PosY(dirY);
	}
	else {
		// ��ǥ Ÿ�Ͽ� �����߰ų� �ſ� ����� ���, ��ǥ Ÿ���� ���� Ÿ�Ϸ� ����
		m_listPathTile.pop_front();
		if (!m_listPathTile.empty()) {
			// ���� Ÿ�Ϸ� �̵��� ����մϴ�.
			Move(_scv);
		}
	}
}
