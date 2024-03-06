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

		//Ÿ���� �ִٸ�
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
			hDC,		// (���� ����)���������� �׸��� �׸� DC ����
			_tank->Get_Rect().left + iScrollX - 12.f, // ���� ���� ��ġ ��ǥ
			_tank->Get_Rect().top + iScrollY - 12.f,
			(int)_tank->Get_Info().fCX,	// ���� ���� �̹����� ����, ����
			(int)_tank->Get_Info().fCY,
			hMemDC,		// ��Ʈ���� ������ �ִ� DC
			(int)_tank->Get_Info().fCX * m_tFrame_SiegeOff.iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
			(int)_tank->Get_Info().fCY * m_tFrame_SiegeOff.iMotion,
			(int)_tank->Get_Info().fCX,	// ����� ��Ʈ�� ����
			(int)_tank->Get_Info().fCY,	// ����� ��Ʈ�� ����
			RGB(0, 0, 0));	// ������ ���� ��
	}
	else
	{
		if (!_tank->Get_Target())
		{
			HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey_SiegeOn);
			GdiTransparentBlt(
				hDC,		// (���� ����)���������� �׸��� �׸� DC ����
				_tank->Get_Rect().left + iScrollX - 12.f, // ���� ���� ��ġ ��ǥ
				_tank->Get_Rect().top + iScrollY - 12.f,
				(int)_tank->Get_Info().fCX,	// ���� ���� �̹����� ����, ����
				(int)_tank->Get_Info().fCY,
				hMemDC,		// ��Ʈ���� ������ �ִ� DC
				(int)_tank->Get_Info().fCX * m_tFrame_SiegeOn.iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
				(int)_tank->Get_Info().fCY * m_tFrame_SiegeOn.iMotion,
				(int)_tank->Get_Info().fCX,	// ����� ��Ʈ�� ����
				(int)_tank->Get_Info().fCY,	// ����� ��Ʈ�� ����
				RGB(0, 0, 0));	// ������ ���� ��
		}
	}

	if (!_tank->Get_Target())
		return;

	HDC	hMemBulletDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey_Attack);

	GdiTransparentBlt(
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		(_tank->Get_Target()->Get_Info().fX + iScrollX) + m_Offset_Attack, // ���� ���� ��ġ ��ǥ
		(_tank->Get_Target()->Get_Info().fY + iScrollY) + m_Offset_Attack,
		m_BulletSizeX,	// ���� ���� �̹����� ����, ����
		m_BulletSizeY,
		hMemBulletDC,		// ��Ʈ���� ������ �ִ� DC
		m_BulletSizeX * m_tFrame_Attack.iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		m_BulletSizeY * m_tFrame_Attack.iMotion,
		m_BulletSizeX,	// ����� ��Ʈ�� ����
		m_BulletSizeY,	// ����� ��Ʈ�� ����
		RGB(0, 0, 0));	// ������ ���� ��

	HDC	hMemSiegeAttackDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey_Attack_Siege);

	GdiTransparentBlt(
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		_tank->Get_Rect().left + iScrollX - 12.f, // ���� ���� ��ġ ��ǥ
		_tank->Get_Rect().top + iScrollY - 12.f,
		128,	// ���� ���� �̹����� ����, ����
		128,
		hMemSiegeAttackDC,		// ��Ʈ���� ������ �ִ� DC
		128 * m_tFrame_Attack_Siege.iFrameStart,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		128 * m_tFrame_Attack_Siege.iMotion,
		128,	// ����� ��Ʈ�� ����
		128,	// ����� ��Ʈ�� ����
		RGB(0, 0, 0));	// ������ ���� ��
}

void CTank_Siege_Mode::Release(CObj_Dynamic*)
{
}

void CTank_Siege_Mode::Move_Frame(CObj_Dynamic* _tank)
{
	//�����尡 �Ǹ� true
	if (_tank->GetBoolSiegeMode())
	{
		//����Ʈ ��� ������ ��ư ������ ��.
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
		//�⺻ �������� �� ��� ���ư��� ���
		else
		{
			//������ �µ� �ѹ��� �ؾ� �Ѵ�.
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
			//���� ������
			else
			{
				*m_pFrameKeyCopy = L"Lower_STank_On";
				m_pFrameCopy->iFrameStart = 5;

				//Ÿ���� �ִٸ�
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
	//�̹� ���� Ÿ������ �ϴ� �ٸ� ������ ���� ���¿���, target->
	if (target == nullptr || target->Get_Dead())
	{
		_tank->Set_Clear_Target();
		return;
	}

	// �̵��ؾ� �� ���� ���� ���
	float dirX = target->Get_Info().fX - _tank->Get_Info().fX;
	float dirY = target->Get_Info().fY - _tank->Get_Info().fY;
	float radian = atan2(dirY, dirX);
	float degree = (radian * 180) / PI;

	if (target != nullptr && !target->Get_Dead())
	{
		// ���� �ð��� �����մϴ�.
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