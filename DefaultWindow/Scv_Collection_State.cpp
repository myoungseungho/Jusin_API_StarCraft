#include "stdafx.h"
#include "Scv_Collection_State.h"
#include "TileMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "EconomyMgr.h"
#include "SoundMgr.h"
CScv_Collection_State::CScv_Collection_State() : m_bCollisionCenter(false), m_AttackFileSize(0), m_Offset_Attack(0), m_CurrentTime(GetTickCount()), m_bGetMineral(false), m_targetMineral(nullptr), m_bCollisionMineral(false)
{
}

CScv_Collection_State::~CScv_Collection_State()
{
}

void CScv_Collection_State::Initialize(CObj_Dynamic* _scv)
{
	m_targetMineral = CObjMgr::Get_Instance()->Get_Target(_scv->GetMousePT().x, _scv->GetMousePT().y);

	m_pFrameCopy = _scv->Get_Frame();
	m_pFrameKeyCopy = _scv->Get_FrameKey();

	*m_pFrameKeyCopy = L"SCV_DOWNLEFT";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 16;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 200;
	m_pFrameCopy->dwTime = GetTickCount();

	m_pFrameKey_Attack = L"SCV_Bullet";
	m_tFrame_Attack.iFrameStart = 0;
	m_tFrame_Attack.iFrameEnd = 9;
	m_tFrame_Attack.iMotion = 0;
	m_tFrame_Attack.dwSpeed = 50;
	m_tFrame_Attack.dwTime = GetTickCount();

	m_AttackFileSize = 48;
	m_Offset_Attack = 0;

	m_CurrentTime = GetTickCount();

	INFO info = _scv->Get_Info();

	int ScvX = info.fX / TILECX;
	int ScvY = info.fY / TILECY;

	int	TileX = m_targetMineral->Get_Info().fX / TILECX;
	int	TileY = m_targetMineral->Get_Info().fY / TILECY;

	Set_Astar(ScvX, ScvY, TileX, TileY);

	m_listPathTile = CTileMgr::Get_Instance()->GetListPath(m_Path);
	m_listPathTile.pop_back();
}

int CScv_Collection_State::Update(CObj_Dynamic* _scv)
{
	if (Move(_scv) == MOVE_OK && !m_bCollisionMineral)
	{
		m_bCollisionMineral = true;

		vector<wchar_t*> m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound(DYNAMIC_OBJ_SCV, SOUND_COLLECTION);
		CSoundMgr::Get_Instance()->PlaySound(m_UnitSound.back(), SOUND_SCV_COLLECTION, 1);
	}

	if (m_bCollisionMineral)
	{
		Collection(_scv);
	}

	if (m_bGetMineral)
	{
		m_bCollisionMineral = false;
		CenterMove(_scv);
	}

	return 0;
}

void CScv_Collection_State::Late_Update(CObj_Dynamic* _scv)
{
	Move_Frame(_scv);
}

void CScv_Collection_State::Render(CObj_Dynamic* _scv, HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	if (m_bCollisionMineral)
	{
		HDC	hBulletDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey_Attack);

		GdiTransparentBlt(
			hDC,		// (���� ����)���������� �׸��� �׸� DC ����
			(_scv->Get_Rect().left + iScrollX), // ���� ���� ��ġ ��ǥ
			(_scv->Get_Rect().top + iScrollY),
			m_AttackFileSize,	// ���� ���� �̹����� ����, ����
			m_AttackFileSize,
			hBulletDC,		// ��Ʈ���� ������ �ִ� DC
			m_AttackFileSize * m_tFrame_Attack.iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
			m_AttackFileSize * m_tFrame_Attack.iMotion,
			m_AttackFileSize,	// ����� ��Ʈ�� ����
			m_AttackFileSize,	// ����� ��Ʈ�� ����
			RGB(0, 0, 0));	// ������ ���� ��
	}


	if (m_bGetMineral)
	{
		HDC	hMinrealDC = CBmpMgr::Get_Instance()->Find_Image(L"SCV_Mineral");

		GdiTransparentBlt(
			hDC,		// (���� ����)���������� �׸��� �׸� DC ����
			(_scv->Get_Rect().left + iScrollX) + 30.f, // ���� ���� ��ġ ��ǥ
			(_scv->Get_Rect().top + iScrollY) + 20.f,
			32,	// ���� ���� �̹����� ����, ����
			32,
			hMinrealDC,		// ��Ʈ���� ������ �ִ� DC
			0,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
			0,
			32,	// ����� ��Ʈ�� ����
			32,	// ����� ��Ʈ�� ����
			RGB(0, 0, 0));	// ������ ���� ��
	}
}

void CScv_Collection_State::Release(CObj_Dynamic*)
{
}

void CScv_Collection_State::Collection(CObj_Dynamic* _scv)
{
	m_CurrentTime++;
	if (m_CurrentTime + 5000 < GetTickCount())
	{
		CObj* center = CObjMgr::Get_Instance()->GetStatic_Obj_List()[STATIC_OBJ_CENTER].front();

		if (center == nullptr)
			return;

		int ScvX = _scv->Get_Info().fX / TILECX;
		int ScvY = _scv->Get_Info().fY / TILECY;

		int	TileX = center->Get_Rect().left / TILECX;
		int	TileY = center->Get_Rect().top / TILECY;

		TileY += 3;
		Set_Astar(ScvX, ScvY, TileX, TileY);

		m_listPathTile = CTileMgr::Get_Instance()->GetListPath(m_Path);

		m_bGetMineral = true;
		m_bCollisionMineral = false;
		m_CurrentTime = GetTickCount();

	}
}

void CScv_Collection_State::CenterMove(CObj_Dynamic* _scv)
{
	CObj* center = CObjMgr::Get_Instance()->GetStatic_Obj_List()[STATIC_OBJ_CENTER].front();

	if (center == nullptr)
		return;

	// ���� ��ǥ Ÿ���� ���ų� ��θ� ��� �Ϸ��� ���
	if (m_listPathTile.empty()) {
		m_bGetMineral = false;
		m_bCollisionCenter = true;
		CEconomyMgr::Get_Instance()->SetMineral();

		//POINT scvPoint = _scv->GetMousePT();
		INFO info = _scv->Get_Info();

		int ScvX = info.fX / TILECX;
		int ScvY = info.fY / TILECY;

		int	TileX = m_targetMineral->Get_Info().fX / TILECX;
		int	TileY = m_targetMineral->Get_Info().fY / TILECY;

		Set_Astar(ScvX, ScvY, TileX, TileY);

		m_listPathTile = CTileMgr::Get_Instance()->GetListPath(m_Path);
		m_listPathTile.pop_back();

		return;
	}

	// ���� ��ǥ Ÿ��
	CObj* currentTargetTile = m_listPathTile.front();

	float unitX = _scv->Get_Info().fX;
	float unitY = _scv->Get_Info().fY;

	// ���� ��ǥ Ÿ���� �߽� ��ǥ ���
	float targetX = currentTargetTile->Get_Info().fX;
	float targetY = currentTargetTile->Get_Info().fY;

	// �̵��ؾ� �� ���� ���� ���
	float dirX = targetX - unitX;
	float dirY = targetY - unitY;
	float radian = atan2(dirY, dirX);
	float degree = (radian * 180) / PI;
	float length = sqrt(dirX * dirX + dirY * dirY);

	// ���� ���� ���Ϳ� �ӵ��� ����Ͽ� �̵�
	float speed = 0.5f; // ������ �ӵ� ��
	if (length > speed) { // ��ǥ������ �Ÿ��� �ӵ����� Ŭ ���, �̵� ����
		dirX = (dirX / length) * speed;
		dirY = (dirY / length) * speed;
		_scv->Set_PosX(dirX);
		_scv->Set_PosY(dirY);

		DetermineKey(_scv, degree);
	}
	else
	{
		// ��ǥ Ÿ�Ͽ� �����߰ų� �ſ� ����� ���, ��ǥ Ÿ���� ���� Ÿ�Ϸ� ����
		m_listPathTile.pop_front();
		if (!m_listPathTile.empty())
		{
			CenterMove(_scv);
		}
	}
}
