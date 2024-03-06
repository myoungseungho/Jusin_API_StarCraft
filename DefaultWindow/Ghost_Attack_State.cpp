#include "stdafx.h"
#include "Ghost_Attack_State.h"

CGhost_Attack_State::CGhost_Attack_State()
{
}

CGhost_Attack_State::~CGhost_Attack_State()
{
}

void CGhost_Attack_State::Initialize(CObj_Dynamic* _ghost)
{
	m_pFrameCopy = _ghost->Get_Frame();
	m_pFrameKeyCopy = _ghost->Get_FrameKey();

	*m_pFrameKeyCopy = L"Ghost_Attack_Right";
	m_pFrameCopy->iFrameStart = 0;
	m_pFrameCopy->iFrameEnd = 0;
	m_pFrameCopy->iMotion = 0;
	m_pFrameCopy->dwSpeed = 200;
	m_pFrameCopy->dwTime = GetTickCount();
}

int CGhost_Attack_State::Update(CObj_Dynamic* _ghost)
{
	//���� ���ݻ����Ÿ��� �ȵ�
	if (!_ghost->GetAttackRun())
		MoveUntilAttackDistance(_ghost);
	//���ݹ��� ���� ��
	else
	{
		Attack(_ghost);
	}

	return 0;
}

void CGhost_Attack_State::Late_Update(CObj_Dynamic*)
{
}

void CGhost_Attack_State::Render(CObj_Dynamic*, HDC hDC)
{
}

void CGhost_Attack_State::Release(CObj_Dynamic*)
{
}

void CGhost_Attack_State::Attack(CObj_Dynamic* _ghost)
{

}

void CGhost_Attack_State::MoveUntilAttackDistance(CObj_Dynamic* _ghost)
{
	POINT pt = _ghost->GetMousePT();
	// �̵��ؾ� �� ���� ���� ���
	float dirX = pt.x - _ghost->Get_Info().fX;
	float dirY = pt.y - _ghost->Get_Info().fY;
	float radian = atan2(dirY, dirX);
	float degree = (radian * 180) / PI;

	float length = sqrt(dirX * dirX + dirY * dirY);

	if (length < _ghost->Get_Stat().m_AttackRange) { // ��ǥ������ �Ÿ��� �ӵ����� Ŭ ���, �̵� ����

		_ghost->SetAttackRun(true);
		DetermineKey(_ghost, degree);
	}
	else
	{
		// ���� ���� ���Ϳ� �ӵ��� ����Ͽ� �̵�
		float speed = _ghost->Get_Stat().m_fSpeed; // ������ �ӵ� ��
		dirX = (dirX / length) * speed;
		dirY = (dirY / length) * speed;
		_ghost->Set_PosX(dirX);
		_ghost->Set_PosY(dirY);

		if (degree > -22.5f && degree <= 22.5f) {
			//����
			*m_pFrameKeyCopy = _ghost->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_RIGHT];
		}
		else if (degree > 22.5f && degree <= 67.5f) {
			// ������
			*m_pFrameKeyCopy = _ghost->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_RDOWN];
		}
		else if (degree > 67.5f && degree <= 112.5f) {
			// ����
			*m_pFrameKeyCopy = _ghost->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_DOWN];
		}
		else if (degree > 112.5f && degree <= 157.5f) {
			// ������
			*m_pFrameKeyCopy = _ghost->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_LDOWN];
		}
		else if ((degree > 157.5f && degree <= 181.f) || (degree <= -157.5f && degree >= -180.f)) {
			// ����
			*m_pFrameKeyCopy = _ghost->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_LEFT];
		}
		else if (degree > -157.5f && degree <= -112.5f) {
			// �ϼ���
			*m_pFrameKeyCopy = _ghost->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_LUP];
		}
		else if (degree > -112.5f && degree <= -67.5f) {
			// ����
			*m_pFrameKeyCopy = _ghost->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_UP];
		}
		else if (degree > -67.5f && degree <= -22.5f) {
			// �ϵ���
			*m_pFrameKeyCopy = _ghost->GetKeyAndFrame()->m_FrameArrayWalkKey[DIR_RUP];
		}
	}
}
