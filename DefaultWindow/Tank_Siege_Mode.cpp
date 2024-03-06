#include "stdafx.h"
#include "Tank_Siege_Mode.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
CTank_Siege_Mode::CTank_Siege_Mode() : m_bIdleReady(false), m_BulletSizeX(0), m_BulletSizeY(0), m_Offset_Attack(0), m_AttackLastTime(0), m_bSiegeOn(false), m_AttackCoolTime(false)
{
}

CTank_Siege_Mode::~CTank_Siege_Mode()
{
}

void CTank_Siege_Mode::Initialize(CObj_Dynamic* _tank)
{
	m_pFrameCopy = _tank->Get_Frame();
	m_pFrameKeyCopy = _tank->Get_FrameKey();

	*m_pFrameKeyCopy = L"Lower_STank_On";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 5;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 200;
	m_pFrameCopy->dwTime = GetTickCount();


	m_pFrameKey_SiegeOn = L"Upper_STank_On";
	m_tFrame_SiegeOn.iFrameStart = 0;
	m_tFrame_SiegeOn.iFrameEnd = 4;
	m_tFrame_SiegeOn.iMotion = 0;
	m_tFrame_SiegeOn.dwSpeed = 200;
	m_tFrame_SiegeOn.dwTime = GetTickCount();

	m_pFrameKey_SiegeOff = L"Upper_STank_Off";
	m_tFrame_SiegeOff.iFrameStart = 0;
	m_tFrame_SiegeOff.iFrameEnd = 4;
	m_tFrame_SiegeOff.iMotion = 0;
	m_tFrame_SiegeOff.dwSpeed = 200;
	m_tFrame_SiegeOff.dwTime = GetTickCount();

	m_pFrameKey_Attack = L"SiegeTank_Attack";
	m_tFrame_Attack.iFrameStart = 0;
	m_tFrame_Attack.iFrameEnd = 14;
	m_tFrame_Attack.iMotion = 0;
	m_tFrame_Attack.dwSpeed = 50;
	m_tFrame_Attack.dwTime = GetTickCount();

	m_pFrameKey_Attack_Siege = L"Upper_STank_Attack_Right";
	m_tFrame_Attack_Siege.iFrameStart = 0;
	m_tFrame_Attack_Siege.iFrameEnd = 0;
	m_tFrame_Attack_Siege.iMotion = 0;
	m_tFrame_Attack_Siege.dwSpeed = 200;
	m_tFrame_Attack_Siege.dwTime = GetTickCount();

	m_BulletSizeX = 100;
	m_BulletSizeY = 108;
	m_Offset_Attack = 0.f;

	_tank->Get_Stat().m_Attack = 30.f;
	_tank->Get_Stat().m_AttackRange = 400.f;
	_tank->Get_Stat().m_DetectionRange = 400.f;

	vector<wchar_t*> m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound(DYNAMIC_OBJ_TANK, SOUND_SIEGE_READY);
	CSoundMgr::Get_Instance()->PlaySound(m_UnitSound.back(), SOUND_TANK_SIEGE_REDAY, 1);
}

int CTank_Siege_Mode::Update(CObj_Dynamic* _tank)
{
	if (_tank->GetBoolSiegeMode())
	{
		_tank->CheckEnemy();

		//타겟이 있다면
		if (_tank->Get_Target())
		{
			Attack(_tank);
		}
	}
	return 0;
}

void CTank_Siege_Mode::Late_Update(CObj_Dynamic* _tank)
{
	Move_Frame(_tank);
}

void CTank_Siege_Mode::Render(CObj_Dynamic* _tank, HDC hDC)
{
	if (!_tank->GetBoolSiegeMode())
		return;

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = nullptr;
	if (m_bIdleReady)
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey_SiegeOff);
		GdiTransparentBlt(
			hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
			_tank->Get_Rect().left + iScrollX - 12.f, // 복사 받을 위치 좌표
			_tank->Get_Rect().top + iScrollY - 12.f,
			(int)_tank->Get_Info().fCX,	// 복사 받을 이미지의 가로, 세로
			(int)_tank->Get_Info().fCY,
			hMemDC,		// 비트맵을 가지고 있는 DC
			(int)_tank->Get_Info().fCX * m_tFrame_SiegeOff.iFrameStart,			// 비트맵 출력 시작 좌표 LEFT, TOP
			(int)_tank->Get_Info().fCY * m_tFrame_SiegeOff.iMotion,
			(int)_tank->Get_Info().fCX,	// 출력할 비트맵 가로
			(int)_tank->Get_Info().fCY,	// 출력할 비트맵 세로
			RGB(0, 0, 0));	// 제거할 색상 값
	}
	else
	{
		if (!_tank->Get_Target())
		{
			HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey_SiegeOn);
			GdiTransparentBlt(
				hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
				_tank->Get_Rect().left + iScrollX - 12.f, // 복사 받을 위치 좌표
				_tank->Get_Rect().top + iScrollY - 12.f,
				(int)_tank->Get_Info().fCX,	// 복사 받을 이미지의 가로, 세로
				(int)_tank->Get_Info().fCY,
				hMemDC,		// 비트맵을 가지고 있는 DC
				(int)_tank->Get_Info().fCX * m_tFrame_SiegeOn.iFrameStart,			// 비트맵 출력 시작 좌표 LEFT, TOP
				(int)_tank->Get_Info().fCY * m_tFrame_SiegeOn.iMotion,
				(int)_tank->Get_Info().fCX,	// 출력할 비트맵 가로
				(int)_tank->Get_Info().fCY,	// 출력할 비트맵 세로
				RGB(0, 0, 0));	// 제거할 색상 값
		}
	}

	if (!_tank->Get_Target())
		return;

	HDC	hMemBulletDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey_Attack);

	GdiTransparentBlt(
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		(_tank->Get_Target()->Get_Info().fX + iScrollX) + m_Offset_Attack, // 복사 받을 위치 좌표
		(_tank->Get_Target()->Get_Info().fY + iScrollY) + m_Offset_Attack,
		m_BulletSizeX,	// 복사 받을 이미지의 가로, 세로
		m_BulletSizeY,
		hMemBulletDC,		// 비트맵을 가지고 있는 DC
		m_BulletSizeX * m_tFrame_Attack.iFrameStart,			// 비트맵 출력 시작 좌표 LEFT, TOP
		m_BulletSizeY * m_tFrame_Attack.iMotion,
		m_BulletSizeX,	// 출력할 비트맵 가로
		m_BulletSizeY,	// 출력할 비트맵 세로
		RGB(0, 0, 0));	// 제거할 색상 값

	HDC	hMemSiegeAttackDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey_Attack_Siege);

	GdiTransparentBlt(
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		_tank->Get_Rect().left + iScrollX - 12.f, // 복사 받을 위치 좌표
		_tank->Get_Rect().top + iScrollY - 12.f,
		128,	// 복사 받을 이미지의 가로, 세로
		128,
		hMemSiegeAttackDC,		// 비트맵을 가지고 있는 DC
		128 * m_tFrame_Attack_Siege.iFrameStart,			// 비트맵 출력 시작 좌표 LEFT, TOP
		128 * m_tFrame_Attack_Siege.iMotion,
		128,	// 출력할 비트맵 가로
		128,	// 출력할 비트맵 세로
		RGB(0, 0, 0));	// 제거할 색상 값
}

void CTank_Siege_Mode::Release(CObj_Dynamic*)
{
}

void CTank_Siege_Mode::Move_Frame(CObj_Dynamic* _tank)
{
	//시즈모드가 되면 true
	if (_tank->GetBoolSiegeMode())
	{
		//디폴트 모드 아이콘 버튼 눌렀을 때.
		if (m_bIdleReady)
		{
			if (m_tFrame_SiegeOff.dwTime + m_tFrame_SiegeOff.dwSpeed < GetTickCount())
			{
				++m_tFrame_SiegeOff.iFrameStart;

				if (m_tFrame_SiegeOff.iFrameStart > m_tFrame_SiegeOff.iFrameEnd)
				{
					m_tFrame_SiegeOff.iFrameStart = 0;

					*m_pFrameKeyCopy = L"Lower_STank_Off";
					m_pFrameCopy->iFrameStart = 0;
					m_pFrameCopy->iFrameEnd = 5;
					m_pFrameCopy->iMotion = 0;
					m_pFrameCopy->dwSpeed = 200;
					m_pFrameCopy->dwTime = GetTickCount();
					m_bIdleReady = false;
					_tank->SetBoolSiegeMode(false);
				}

				m_tFrame_SiegeOff.dwTime = GetTickCount();
			}
		}
		//기본 시즈모드일 때 계속 돌아가는 모드
		else
		{
			//시즈모드 온도 한번만 해야 한다.
			if (!m_bSiegeOn)
			{
				if (m_tFrame_SiegeOn.dwTime + m_tFrame_SiegeOn.dwSpeed < GetTickCount())
				{
					++m_tFrame_SiegeOn.iFrameStart;

					if (m_tFrame_SiegeOn.iFrameStart > m_tFrame_SiegeOn.iFrameEnd)
					{
						m_tFrame_SiegeOn.iFrameStart = m_tFrame_SiegeOn.iFrameEnd;
						m_bSiegeOn = true;
					}

					m_tFrame_SiegeOn.dwTime = GetTickCount();
				}
			}
			//평상시 시즈모드
			else
			{
				*m_pFrameKeyCopy = L"Lower_STank_On";
				m_pFrameCopy->iFrameStart = 5;

				//타겟이 있다면
				if (_tank->Get_Target())
				{
					if (m_tFrame_Attack_Siege.dwTime + m_tFrame_Attack_Siege.dwSpeed < GetTickCount())
					{
						++m_tFrame_Attack_Siege.iFrameStart;

						if (m_tFrame_Attack_Siege.iFrameStart > m_tFrame_Attack_Siege.iFrameEnd)
						{
							m_tFrame_Attack_Siege.iFrameStart = 0;
						}

						m_tFrame_Attack_Siege.dwTime = GetTickCount();
					}

					if (!m_AttackCoolTime)
						return;

					DWORD currentTime = GetTickCount();

					if (m_tFrame_Attack.dwTime + m_tFrame_Attack.dwSpeed < GetTickCount())
					{
						++m_tFrame_Attack.iFrameStart;

						if (m_tFrame_Attack.iFrameStart > m_tFrame_Attack.iFrameEnd)
						{
							m_tFrame_Attack.iFrameStart = 0;
							m_AttackCoolTime = false;
						}

						m_tFrame_Attack.dwTime = GetTickCount();
					}
				}
			}
		}
	}
}

void CTank_Siege_Mode::Attack(CObj_Dynamic* _tank)
{
	CObj* target = _tank->Get_Target();
	//이미 동일 타겟으로 하는 다른 유닛이 죽인 상태에서, target->
	if (target == nullptr || target->Get_Dead())
	{
		_tank->Set_Clear_Target();
		return;
	}

	// 이동해야 할 방향 벡터 계산
	float dirX = target->Get_Info().fX - _tank->Get_Info().fX;
	float dirY = target->Get_Info().fY - _tank->Get_Info().fY;
	float radian = atan2(dirY, dirX);
	float degree = (radian * 180) / PI;

	if (target != nullptr && !target->Get_Dead())
	{
		// 현재 시간을 측정합니다.
		DWORD currentTime = GetTickCount64();
		if (currentTime - m_AttackLastTime >= 5000)
		{
			CObj_Dynamic* dynamicObj = dynamic_cast<CObj_Dynamic*>(target);
			if (dynamicObj != nullptr)
			{
				vector<wchar_t*> m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound(DYNAMIC_OBJ_TANK, SOUND_SIEGE_ATTACK);
				CSoundMgr::Get_Instance()->PlaySound(m_UnitSound.back(), SOUND_TANK_SIEGE_ATTACK, 1);

				DetermineKey(_tank, degree);

				list<CObj*> nearObjList = CObjMgr::Get_Instance()->GetNearUnit(dynamicObj, 50.f);
				for (auto iter : nearObjList)
				{
					dynamic_cast<CObj_Dynamic*>(iter)->Set_Damage(_tank->Get_Stat().m_Attack);
				}

				m_AttackLastTime = currentTime;
				m_AttackCoolTime = true;
			}
		}
	}
}

void CTank_Siege_Mode::SetDefaultMode()
{
	vector<wchar_t*> m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound(DYNAMIC_OBJ_TANK, SOUND_SIEGE_READY);
	CSoundMgr::Get_Instance()->PlaySound(m_UnitSound.back(), SOUND_TANK_SIEGE_REDAY, 1);

	m_bIdleReady = true;
	m_bSiegeOn = false;
	*m_pFrameKeyCopy = L"Lower_STank_Off";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 5;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 200;
	m_pFrameCopy->dwTime = GetTickCount();
}