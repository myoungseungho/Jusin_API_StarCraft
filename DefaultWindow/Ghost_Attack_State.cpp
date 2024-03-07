#include "stdafx.h"
#include "Ghost_Attack_State.h"
#include "Nuclear.h"
#include "SpawnMgr.h"
#include "Nuclear_Target.h"
#include "SoundMgr.h"
CGhost_Attack_State::CGhost_Attack_State() :m_CurrentTime(GetTickCount())
{
}

CGhost_Attack_State::~CGhost_Attack_State()
{
}

void CGhost_Attack_State::Initialize(CObj_Dynamic* _ghost)
{
	_ghost->SetAttackRun(false);
	m_CurrentTime = GetTickCount();
	m_pFrameCopy = _ghost->Get_Frame();
	m_pFrameKeyCopy = _ghost->Get_FrameKey();

	*m_pFrameKeyCopy = L"Ghost_Walk_Down_Right";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 17;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 50;
	m_pFrameCopy->dwTime = GetTickCount();
}

int CGhost_Attack_State::Update(CObj_Dynamic* _ghost)
{
	//아직 공격사정거리는 안됨
	if (!_ghost->GetAttackRun())
		MoveUntilAttackDistance(_ghost);
	//공격범위 까지 감
	else
	{
		Attack(_ghost);
	}

	return 0;
}

void CGhost_Attack_State::Late_Update(CObj_Dynamic* _ghost)
{
	__super::Move_Frame(_ghost);
}

void CGhost_Attack_State::Render(CObj_Dynamic*, HDC hDC)
{
}

void CGhost_Attack_State::Release(CObj_Dynamic*)
{
}

void CGhost_Attack_State::Attack(CObj_Dynamic* _ghost)
{
	m_CurrentTime++;

	if (m_CurrentTime + 5000 < GetTickCount())
	{
		CObjMgr::Get_Instance()->Delete_ID_DynamicObj(DYNAMIC_OBJ_NUCLEAR_TARGET);
		m_CurrentTime = GetTickCount();
		POINT targetPt = _ghost->GetMousePT();
		CObj_Dynamic* nuclear = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CNuclear>(DYNAMIC_OBJ_NUCLEAR, FACTION_END, targetPt.x, targetPt.y);
		_ghost->ChangeState(IDLE_STATE);
	}
}

void CGhost_Attack_State::MoveUntilAttackDistance(CObj_Dynamic* _ghost)
{
	POINT pt = _ghost->GetMousePT();
	// 이동해야 할 방향 벡터 계산
	float dirX = pt.x - _ghost->Get_Info().fX;
	float dirY = pt.y - _ghost->Get_Info().fY;
	float radian = atan2(dirY, dirX);
	float degree = (radian * 180) / PI;

	float length = sqrt(dirX * dirX + dirY * dirY);

	if (length < _ghost->Get_Stat().m_AttackRange) { // 목표까지의 거리가 속도보다 클 경우, 이동 실행

		vector<wchar_t*> m_UnitSound = CSoundMgr::Get_Instance()->GetUnitSound(DYNAMIC_OBJ_GHOST, SOUND_ATTACK);
		CSoundMgr::Get_Instance()->PlaySound(m_UnitSound.back(), SOUND_GHOST_ATTACK, 1);
		_ghost->SetAttackRun(true);
		DetermineKey(_ghost, degree);
		CObj_Dynamic* nuclear_Target = CSpawnMgr::Get_Instance()->Spawn_DynamicObj<CNuclear_Target>(DYNAMIC_OBJ_NUCLEAR_TARGET, FACTION_END, pt.x, pt.y);
	}
	else
	{
		// 단위 방향 벡터와 속도를 사용하여 이동
		float speed = _ghost->Get_Stat().m_fSpeed; // 적당한 속도 값
		dirX = (dirX / length) * speed;
		dirY = (dirY / length) * speed;
		_ghost->Set_PosX(dirX);
		_ghost->Set_PosY(dirY);

		if (degree > -22.5f && degree <= 22.5f) {
			//동쪽
			*m_pFrameKeyCopy = _ghost->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_RIGHT];
		}
		else if (degree > 22.5f && degree <= 67.5f) {
			// 남동쪽
			*m_pFrameKeyCopy = _ghost->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_RDOWN];
		}
		else if (degree > 67.5f && degree <= 112.5f) {
			// 남쪽
			*m_pFrameKeyCopy = _ghost->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_DOWN];
		}
		else if (degree > 112.5f && degree <= 157.5f) {
			// 남서쪽
			*m_pFrameKeyCopy = _ghost->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_LDOWN];
		}
		else if ((degree > 157.5f && degree <= 181.f) || (degree <= -157.5f && degree >= -180.f)) {
			// 서쪽
			*m_pFrameKeyCopy = _ghost->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_LEFT];
		}
		else if (degree > -157.5f && degree <= -112.5f) {
			// 북서쪽
			*m_pFrameKeyCopy = _ghost->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_LUP];
		}
		else if (degree > -112.5f && degree <= -67.5f) {
			// 북쪽
			*m_pFrameKeyCopy = _ghost->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_UP];
		}
		else if (degree > -67.5f && degree <= -22.5f) {
			// 북동쪽
			*m_pFrameKeyCopy = _ghost->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_RUP];
		}

		if (*m_pFrameKeyCopy != *m_pFrameKeyCopy)
		{
			m_pFrameCopy->iFrameStart = _ghost->GetKeyAndFrame()->_mapKeyFrame[*m_pFrameKeyCopy].iFrameStart;
			m_pFrameCopy->dwTime = _ghost->GetKeyAndFrame()->_mapKeyFrame[*m_pFrameKeyCopy].dwTime;
		}


		m_pFrameCopy->iFrameEnd = _ghost->GetKeyAndFrame()->_mapKeyFrame[*m_pFrameKeyCopy].iFrameEnd;
		m_pFrameCopy->iMotion = _ghost->GetKeyAndFrame()->_mapKeyFrame[*m_pFrameKeyCopy].iMotion;
		m_pFrameCopy->dwSpeed = _ghost->GetKeyAndFrame()->_mapKeyFrame[*m_pFrameKeyCopy].dwSpeed;
	}
}

void CGhost_Attack_State::Move_Frame(CObj_Dynamic* _ghost)
{

}
