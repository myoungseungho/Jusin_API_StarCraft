#include "stdafx.h"
#include "UI_Text_Mgr.h"

CUI_Text_Mgr::CUI_Text_Mgr() : m_ClieckObj(nullptr)
{
}

CUI_Text_Mgr::~CUI_Text_Mgr()
{
}

void CUI_Text_Mgr::Initialize()
{
}

void CUI_Text_Mgr::Render(HDC _hdc)
{
	if (m_ClieckObj == nullptr || m_ClieckObj->Get_Dead())
		return;

	RECT rect = { 230,520,330,620 };
	RECT rect2 = { 380,450,480,550 };
	STAT stat = m_ClieckObj->Get_Stat();

	TCHAR buffer[100]; // ���۸� �غ��մϴ�.
	wsprintf(buffer, TEXT("%d/%d"), stat.m_Hp, stat.m_MaxHp); // HP�� MaxHP�� ����ȭ�մϴ�.
	TCHAR buffer2[100]; // ���۸� �غ��մϴ�.
	wsprintf(buffer2, TEXT("%s"), stat.m_Name); // HP�� MaxHP�� ����ȭ�մϴ�.

	// ����� �����ϰ� ����
	SetBkMode(_hdc, TRANSPARENT);

	// �ؽ�Ʈ ������ �ʷϻ����� ����
	SetTextColor(_hdc, RGB(0, 255, 0));
	DrawText(_hdc, buffer, -1, &rect, DT_LEFT | DT_SINGLELINE | DT_VCENTER);
	// �ؽ�Ʈ ������ ������� ����
	SetTextColor(_hdc, RGB(255, 255, 255));
	DrawText(_hdc, buffer2, -1, &rect2, DT_LEFT | DT_SINGLELINE | DT_VCENTER);
}

void CUI_Text_Mgr::OnClickObj(CObj* _unit)
{
	m_ClieckObj = _unit;
}

void CUI_Text_Mgr::SetClear_Text()
{
	m_ClieckObj = nullptr;
}
