#include "stdafx.h"
#include "Medic.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Medic_Idle_State.h"
#include "Medic_Walk_State.h"
#include "Medic_Attack_State.h"
#include "Medic_Die_State.h"
#include "ObjMgr.h"
#include "SpawnMgr.h"
#include "UI_Medic_Display.h"
CMedic::CMedic()
{
	InsertBmpFile();
}

CMedic::~CMedic()
{
	Release();
}

void CMedic::Initialize()
{
	if (m_CurrentState == NON_STATE)
	{
		m_eRender = RENDER_GAMEOBJECT;

		//처음 크기 고정
		m_tInfo.fCX = 64.f;
		m_tInfo.fCY = 64.f;

		m_vecState.push_back(new CMedic_Idle_State);
		m_vecState.push_back(new CMedic_Walk_State);
		m_vecState.push_back(new CMedic_Attack_State);
		m_vecState.push_back(new CMedic_Die_State);

		ChangeState(IDLE_STATE);

		m_Stat.m_Hp = 60.f;
		m_Stat.m_MaxHp = 60.f;
		m_Stat.m_Attack = -1.f;
		m_Stat.m_fSpeed = 3.f;
		m_Stat.m_AttackRange = 50.f;
		m_Stat.m_DetectionRange = 300.f;
		lstrcpyW(m_Stat.m_Name, L"Medic");
	}
}

int CMedic::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	__super::Update_Rect();

	m_vecState[m_CurrentState]->Update(this);

	if (m_bCliecked && m_DisPlayCopy == nullptr)
	{
		m_DisPlayCopy = CSpawnMgr::Get_Instance()->Spawn_UIObj<CUI_Medic_Display>(UI_OBJECT_DISPLAY);
	}
	else if (!m_bCliecked && m_DisPlayCopy != nullptr)
	{
		CObjMgr::Get_Instance()->Delete_ID_UIObj(UI_OBJECT_DISPLAY);
		m_DisPlayCopy = nullptr;
	}
	return OBJ_NOEVENT;
}

void CMedic::Late_Update()
{
	m_vecState[m_CurrentState]->Late_Update(this);

	__super::Move_Frame();
}

void CMedic::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	int grade = m_Stat.m_MaxHp / 6;
	int currentGrade = m_Stat.m_Hp / grade;
	int frame = currentGrade == 0 ? 5 : currentGrade == 1 ? 5 : currentGrade == 2 ? 4 : currentGrade == 3 ? 3
		: currentGrade == 4 ? 2 : currentGrade == 5 ? 1 : currentGrade == 6 ? 0 : 0;

	HDC	hhpDC = CBmpMgr::Get_Instance()->Find_Image(L"Small_Hp");

	GdiTransparentBlt(
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		m_tRect.left + iScrollX + 15.f, // 복사 받을 위치 좌표
		m_tRect.top + iScrollY + (int)m_tInfo.fCY - 15.f,
		32,	// 복사 받을 이미지의 가로, 세로
		5,
		hhpDC,		// 비트맵을 가지고 있는 DC
		32 * frame,			// 비트맵 출력 시작 좌표 LEFT, TOP
		5 * m_tFrame.iMotion,
		32,	// 출력할 비트맵 가로
		5,	// 출력할 비트맵 세로
		RGB(0, 0, 0));	// 제거할 색상 값

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

	if (!m_bCliecked)
		return;

	HDC	hSelectDC = nullptr;
	if (this->Get_FactionState() == FACTION_ALLY)
		hSelectDC = CBmpMgr::Get_Instance()->Find_Image(L"PSelect2");
	else if (this->Get_FactionState() == FACTION_ENEMY)
		hSelectDC = CBmpMgr::Get_Instance()->Find_Image(L"ESelect2");

	GdiTransparentBlt(
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		this->m_tRect.left + iScrollX, // 복사 받을 위치 좌표
		this->m_tRect.top + iScrollY,
		64,	// 복사 받을 이미지의 가로, 세로
		64,
		hSelectDC,		// 비트맵을 가지고 있는 DC
		0,			// 비트맵 출력 시작 좌표 LEFT, TOP
		0,
		64,	// 출력할 비트맵 가로
		64,	// 출력할 비트맵 세로
		RGB(0, 0, 0));	// 제거할 색상 값
}

void CMedic::Release()
{
	m_vecState[m_CurrentState]->Release(this);
}

bool CMedic::CheckEnemy()
{
	list<CObj*>* pList = CObjMgr::Get_Instance()->GetDynamic_Obj_List();
	float nearDistnace = (numeric_limits<float>::max)();
	CObj* target = nullptr;

	for (size_t i = 0; i < DYNAMIC_OBJ_END; i++)
	{
		for (auto iter : pList[i])
		{
			if (iter == this || iter->Get_FactionState() != this->Get_FactionState() || iter->Get_Stat().m_Hp == iter->Get_Stat().m_MaxHp || dynamic_cast<CObj_Dynamic*>(iter)->GetType() == DYNAMIC_OBJ_TANK)
				continue;

			float distance = sqrt((iter->Get_Info().fX - m_tInfo.fX) * (iter->Get_Info().fX - m_tInfo.fX) + (iter->Get_Info().fY - m_tInfo.fY) * (iter->Get_Info().fY - m_tInfo.fY));

			if (distance < nearDistnace)
			{
				nearDistnace = distance;
				target = iter;
			}
		}
	}

	if (m_Stat.m_DetectionRange > nearDistnace)
	{
		if (m_CurrentState != ATTACK_STATE)
		{
			ChangeState(ATTACK_STATE);
			m_pTarget = target;
			return true;
		}
	}

	m_pTarget = nullptr;
	return false;
}

void CMedic::InsertBmpFile()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Idle/Medic_Idle.bmp", L"Medic_Idle");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Work/Medic_Walk_Up.bmp", L"Medic_Walk_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Work/Medic_Walk_Up_Right_60.bmp", L"Medic_Walk_Up_Right_60");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Work/Medic_Walk_Right_90.bmp", L"Medic_Walk_Right_90");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Work/Medic_Walk_Down_Right_150.bmp", L"Medic_Walk_Down_Right_150");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Work/Medic_Walk_Down.bmp", L"Medic_Walk_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Work/Medic_Walk_Down_Left.bmp", L"Medic_Walk_Down_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Work/Medic_Walk_Left.bmp", L"Medic_Walk_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Work/Medic_Walk_Up_Left.bmp", L"Medic_Walk_Up_Left");

	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_UP] = (L"Medic_Walk_Up");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_UP],{0,13,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RUP] = (L"Medic_Walk_Up_Right_60");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RUP],{0,13,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RIGHT] = (L"Medic_Walk_Right_90");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RIGHT],{0,13,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RDOWN] = (L"Medic_Walk_Down_Right_150");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_RDOWN],{0,13,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_DOWN] = (L"Medic_Walk_Down");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_DOWN],{0,6,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LDOWN] = (L"Medic_Walk_Down_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LDOWN],{0,2,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LEFT] = (L"Medic_Walk_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LEFT],{0,6,0,50,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LUP] = (L"Medic_Walk_Up_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayWalkKey[DIR_LUP],{0,6,0,50,GetTickCount()} });

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Attack/Medic_Attack_Up.bmp", L"Medic_Attack_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Attack/Medic_Attack_Up_Right_45.bmp", L"Medic_Attack_Up_Right_45");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Attack/Medic_Attack_Right.bmp", L"Medic_Attack_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Attack/Medic_Attack_Down_Right_150.bmp", L"Medic_Attack_Down_Right_150");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Attack/Medic_Attack_Down.bmp", L"Medic_Attack_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Attack/Medic_Attack_Down_Left.bmp", L"Medic_Attack_Down_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Attack/Medic_Attack_Left.bmp", L"Medic_Attack_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Attack/Medic_Attack_Up_Left.bmp", L"Medic_Attack_Up_Left");

	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_UP] = (L"Medic_Attack_Up");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_UP],{0,3,0,100,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RUP] = (L"Medic_Attack_Up_Right_45");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RUP],{0,3,0,100,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RIGHT] = (L"Medic_Attack_Right");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RIGHT],{0,3,0,100,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RDOWN] = (L"Medic_Attack_Down_Right_150");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_RDOWN],{0,3,0,100,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_DOWN] = (L"Medic_Attack_Down");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_DOWN],{0,1,0,100,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LDOWN] = (L"Medic_Attack_Down_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LDOWN],{0,3,0,100,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LEFT] = (L"Medic_Attack_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LEFT],{0,3,0,100,GetTickCount()} });
	m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LUP] = (L"Medic_Attack_Up_Left");
	m_KeyAndFrame._mapKeyFrame.insert({ m_KeyAndFrame.m_FrameArrayAttackKey[DIR_LUP],{0,3,0,100,GetTickCount()} });


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Unit/Medic/Die/Medic_Die.bmp", L"Medic_Die");
}

DYNAMIC_OBJID CMedic::GetType() const
{
	return DYNAMIC_OBJ_MEDIC;
}
