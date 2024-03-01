#include "stdafx.h"
#include "UI_Text_Mgr.h"

CUI_Text_Mgr::CUI_Text_Mgr() : m_clieckObj(nullptr)
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
	if (m_clieckObj == nullptr)
		return;

	RECT rect = { 230,520,330,620 };
	STAT stat = m_clieckObj->Get_Stat();

	TCHAR buffer[100]; // ���۸� �غ��մϴ�.
	wsprintf(buffer, TEXT("%d/%d"), stat.m_Hp, stat.m_MaxHp); // HP�� MaxHP�� ����ȭ�մϴ�.

	// ����� �����ϰ� ����
	SetBkMode(_hdc, TRANSPARENT);

	// �ؽ�Ʈ ������ �ʷϻ����� ����
	SetTextColor(_hdc, RGB(0, 255, 0));

	DrawText(_hdc, buffer, -1, &rect, DT_LEFT | DT_SINGLELINE | DT_VCENTER); // ����ȭ�� �ؽ�Ʈ�� ����մϴ�.
}

void CUI_Text_Mgr::OnClickObj(CObj* _unit)
{
	m_clieckObj = _unit;
}

void CUI_Text_Mgr::SetClear_Text()
{
	m_clieckObj = nullptr;
}
