#include "stdafx.h"
#include "UI_Text_Mgr.h"
#include "EconomyMgr.h"
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
	MINERALGASPEOPLE resource = CEconomyMgr::Get_Instance()->GetResource();

	RECT rectMineralResource = { 585,17,630,27 };
	TCHAR buffer1[100]; // ���۸� �غ��մϴ�.
	wsprintf(buffer1, TEXT("%d"), resource.m_Mineral);

	RECT rectGasResource = { 668,17,713,27 };
	TCHAR buffer2[100]; // ���۸� �غ��մϴ�.
	wsprintf(buffer2, TEXT("%d"), resource.m_Gas);

	RECT rectPeopleResource = { 748,17,800,27 };
	TCHAR buffer3[100]; // ���۸� �غ��մϴ�.
	wsprintf(buffer3, TEXT("%d/%d"), resource.m_People, resource.m_MaxPeople);

		// ����� �����ϰ� ����
	SetBkMode(_hdc, TRANSPARENT);

	SetTextColor(_hdc, RGB(0, 255, 0));
	DrawText(_hdc, buffer1, -1, &rectMineralResource, DT_LEFT | DT_SINGLELINE | DT_VCENTER);
	SetTextColor(_hdc, RGB(0, 255, 0));
	DrawText(_hdc, buffer2, -1, &rectGasResource, DT_LEFT | DT_SINGLELINE | DT_VCENTER);
	SetTextColor(_hdc, RGB(0, 255, 0));
	DrawText(_hdc, buffer3, -1, &rectPeopleResource, DT_LEFT | DT_SINGLELINE | DT_VCENTER);


	if (m_ClieckObj == nullptr || m_ClieckObj->Get_Dead())
		return;

	RECT rect = { 230,520,330,620 };
	RECT rect2 = { 350,450,470,550 };
	STAT stat = m_ClieckObj->Get_Stat();

	TCHAR buffer4[100]; // ���۸� �غ��մϴ�.
	wsprintf(buffer4, TEXT("%d/%d"), stat.m_Hp, stat.m_MaxHp); // HP�� MaxHP�� ����ȭ�մϴ�.
	TCHAR buffer5[100]; // ���۸� �غ��մϴ�.
	wsprintf(buffer5, TEXT("%s"), stat.m_Name); // HP�� MaxHP�� ����ȭ�մϴ�.

	//// ����� �����ϰ� ����
	//SetBkMode(_hdc, TRANSPARENT);

	// �ؽ�Ʈ ������ �ʷϻ����� ����
	SetTextColor(_hdc, RGB(0, 255, 0));
	DrawText(_hdc, buffer4, -1, &rect, DT_LEFT | DT_SINGLELINE | DT_VCENTER);
	// �ؽ�Ʈ ������ ������� ����
	SetTextColor(_hdc, RGB(255, 255, 255));
	DrawText(_hdc, buffer5, -1, &rect2, DT_LEFT | DT_SINGLELINE | DT_VCENTER);
}

void CUI_Text_Mgr::OnClickObj(CObj* _unit)
{
	m_ClieckObj = _unit;
}

void CUI_Text_Mgr::SetClear_Text()
{
	m_ClieckObj = nullptr;
}
