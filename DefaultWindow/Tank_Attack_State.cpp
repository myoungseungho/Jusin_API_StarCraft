#include "stdafx.h"
#include "Tank_Attack_State.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
CTank_Attack_State::CTank_Attack_State() : m_CurrentTimeAttackPosin(GetTickCount())
{
}

CTank_Attack_State::~CTank_Attack_State()
{
}

void CTank_Attack_State::Initialize(CObj_Dynamic* _tank)
{
	m_pFrameCopy = _tank->Get_Frame();
	m_pFrameKeyCopy = _tank->Get_FrameKey();

	*m_pFrameKeyCopy = L"Lower_Tank_Walk_Right_90";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 5;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 50;
	m_pFrameCopy->dwTime = GetTickCount();


	m_pFrameKey_TankPosin = L"Tank_Upper_Right";
	m_tFrame_TankPosin.iFrameStart = 0;
	m_tFrame_TankPosin.iFrameEnd = 0;
	m_tFrame_TankPosin.iMotion = 0;
	m_tFrame_TankPosin.dwSpeed = 50;
	m_tFrame_TankPosin.dwTime = GetTickCount();


	m_pFrameKey_Attack_TankPosin = L"TankLaunch_Right";
	m_tFrame_Attack_TankPosin.iFrameStart = 0;
	m_tFrame_Attack_TankPosin.iFrameEnd = 0;
	m_tFrame_Attack_TankPosin.iMotion = 0;
	m_tFrame_Attack_TankPosin.dwSpeed = 200;
	m_tFrame_Attack_TankPosin.dwTime = GetTickCount();

	m_pFrameKey_Attack = L"TankHit";
	m_tFrame_Attack.iFrameStart = 0;
	m_tFrame_Attack.iFrameEnd = 12;
	m_tFrame_Attack.iMotion = 0;
	m_tFrame_Attack.dwSpeed = 150;
	m_tFrame_Attack.dwTime = GetTickCount();

	m_TankPosinSize = 128;
	m_TankPosinLaunchSize = 128;
	m_BulletSize = 44;
	m_Offset_Attack = 0.f;

	_tank->SetAttackRun(false);
}

int CTank_Attack_State::Update(CObj_Dynamic* _tank)
{
	//타겟이 있다면
	if (_tank->Get_Target())
	{
		//아직 공격사정거리는 안됨
		if (!_tank->GetAttackRun())
			MoveUntilAttackDistance(_tank);
		//공격범위 까지 감
		else
		{
			Attack(_tank);
		}
	}
	//타겟이 없다면
	else
	{

		if (!_tank->CheckEnemy())
			_tank->ChangeState(IDLE_STATE);
	}

	return 0;
}

void CTank_Attack_State::Late_Update(CObj_Dynamic* _tank)
{
	Move_Frame(_tank);
}

void CTank_Attack_State::Render(CObj_Dynamic* _tank, HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey_TankPosin);

	GdiTransparentBlt(
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		(_tank->Get_Rect().left + iScrollX), // 복사 받을 위치 좌표
		(_tank->Get_Rect().top + iScrollY),
		m_TankPosinSize,	// 복사 받을 이미지의 가로, 세로
		m_TankPosinSize,
		hMemDC,		// 비트맵을 가지고 있는 DC
		m_TankPosinSize * m_tFrame_TankPosin.iFrameStart,			// 비트맵 출력 시작 좌표 LEFT, TOP
		m_TankPosinSize * m_tFrame_TankPosin.iMotion,
		m_TankPosinSize,	// 출력할 비트맵 가로
		m_TankPosinSize,	// 출력할 비트맵 세로
		RGB(0, 0, 0));	// 제거할 색상 값

	if (!_tank->GetAttackRun())
		return;

	if (m_CurrentTimeAttackPosin + 2000 < GetTickCount())
	{
		m_CurrentTimeAttackPosin = GetTickCount();
		HDC	hMemLaunchDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey_Attack_TankPosin);

		GdiTransparentBlt(
			hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
			(_tank->Get_Rect().left + iScrollX), // 복사 받을 위치 좌표
			(_tank->Get_Rect().top + iScrollY),
			m_TankPosinLaunchSize,	// 복사 받을 이미지의 가로, 세로
			m_TankPosinLaunchSize,
			hMemLaunchDC,		// 비트맵을 가지고 있는 DC
			m_TankPosinLaunchSize * m_tFrame_Attack_TankPosin.iFrameStart,			// 비트맵 출력 시작 좌표 LEFT, TOP
			m_TankPosinLaunchSize * m_tFrame_Attack_TankPosin.iMotion,
			m_TankPosinLaunchSize,	// 출력할 비트맵 가로
			m_TankPosinLaunchSize,	// 출력할 비트맵 세로
			RGB(0, 0, 0));	// 제거할 색상 값
	}

	HDC	hMemBulletDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey_Attack);

	GdiTransparentBlt(
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		(_tank->Get_Target()->Get_Rect().left + iScrollX) + m_Offset_Attack, // 복사 받을 위치 좌표
		(_tank->Get_Target()->Get_Rect().top + iScrollY) + m_Offset_Attack,
		m_BulletSize,	// 복사 받을 이미지의 가로, 세로
		m_BulletSize,
		hMemBulletDC,		// 비트맵을 가지고 있는 DC
		m_BulletSize * m_tFrame_Attack.iFrameStart,			// 비트맵 출력 시작 좌표 LEFT, TOP
		m_BulletSize * m_tFrame_Attack.iMotion,
		m_BulletSize,	// 출력할 비트맵 가로
		m_BulletSize,	// 출력할 비트맵 세로
		RGB(0, 0, 0));	// 제거할 색상 값
}

void CTank_Attack_State::Release(CObj_Dynamic*)
{
}

void CTank_Attack_State::Move_Frame(CObj_Dynamic* _tank)
{
	if (m_tFrame_TankPosin.dwTime + m_tFrame_TankPosin.dwSpeed < GetTickCount())
	{
		++m_tFrame_TankPosin.iFrameStart;

		if (m_tFrame_TankPosin.iFrameStart > m_tFrame_TankPosin.iFrameEnd)
		{
			m_tFrame_TankPosin.iFrameStart = 0;
		}

		m_tFrame_TankPosin.dwTime = GetTickCount();
	}

	if (_tank->GetAttackRun())
	{
		if (m_tFrame_Attack.dwTime + m_tFrame_Attack.dwSpeed < GetTickCount())
		{
			++m_tFrame_Attack.iFrameStart;

			if (m_tFrame_Attack.iFrameStart > m_tFrame_Attack.iFrameEnd)
			{
				m_tFrame_Attack.iFrameStart = 0;
			}

			m_tFrame_Attack.dwTime = GetTickCount();
		}
	}
}

void CTank_Attack_State::Attack(CObj_Dynamic* _unit)
{
	IAttackState::Attack(_unit);
}

