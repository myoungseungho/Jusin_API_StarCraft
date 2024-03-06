#include "stdafx.h"
#include "UI_MiniMap.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "Obj_Dynamic.h"
#include "ScrollMgr.h"
#include "Obj_Static.h"
CUI_MiniMap::CUI_MiniMap()
{
}

CUI_MiniMap::~CUI_MiniMap()
{
}

void CUI_MiniMap::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Single/MiniMap.bmp", L"MiniMap");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Single/MiniMapCurrent.bmp", L"MiniMapCurrent");

	m_eRender = RENDER_UI;
}

int CUI_MiniMap::Update()
{
	return 0;
}

void CUI_MiniMap::Late_Update()
{
}

void CUI_MiniMap::Render(HDC hDC)
{
	HDC	hUIDC = CBmpMgr::Get_Instance()->Find_Image(L"MiniMap");
	GdiTransparentBlt(
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		8, // ���� ���� ��ġ ��ǥ
		430,
		161,	// ���� ���� �̹����� ����, ����
		166,
		hUIDC,		// ��Ʈ���� ������ �ִ� DC
		0,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		0,
		161,	// ����� ��Ʈ�� ����
		166,	// ����� ��Ʈ�� ����
		RGB(0, 0, 0));	// ������ ���� ��

	for (size_t i = 0; i < DYNAMIC_OBJ_END; i++)
	{
		for (auto iter : CObjMgr::Get_Instance()->GetDynamic_Obj_List()[i])
		{
			CObj_Dynamic* dynamicIter = dynamic_cast<CObj_Dynamic*>(iter);

			float unitX = 0.f;
			float unitY = 0.f;

			unitX = dynamicIter->Get_Info().fX;
			unitY = dynamicIter->Get_Info().fY;

			// ������ �̴ϸ� ���� ��ġ ���
			float miniMapX = (unitX * 161.f) / 4096.f;
			float miniMapY = (unitY * 166.f) / 4096.f;

			int screenX = 8 + static_cast<int>(miniMapX);
			int screenY = 430 + static_cast<int>(miniMapY);

			// �簢���� ũ�⸦ �����մϴ�.
			int rectSize = 5;

			COLORREF color;

			if (dynamicIter->Get_FactionState() == FACTION_ALLY)
			{
				// �ʷϻ� �귯�� ����
				color = RGB(0, 255, 0); // �ʷϻ�
			}
			else if (dynamicIter->Get_FactionState() == FACTION_ENEMY)
			{
				// ������ �귯�� ����
				color = RGB(255, 0, 0); // ������
			}
			else
				return;

			// �簢�� �׸���
			HBRUSH hBrush = CreateSolidBrush(color); // �������� �귯�� ����
			HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			// �簢�� �׸��� (�̴ϸ� ���� ���� ��ġ��)
			Rectangle(hDC, screenX, screenY, screenX + rectSize, screenY + rectSize);

			// ����
			SelectObject(hDC, hOldBrush); // ���� �귯�÷� ����
			DeleteObject(hBrush); // ����� �귯�� ����
		}
	}

	for (size_t i = 0; i < STATIC_OBJ_MINERAL; i++)
	{
		for (auto iter : CObjMgr::Get_Instance()->GetStatic_Obj_List()[i])
		{
			CObj_Static* staticIter = dynamic_cast<CObj_Static*>(iter);

			float unitX = 0.f;
			float unitY = 0.f;

			unitX = staticIter->Get_Info().fX;
			unitY = staticIter->Get_Info().fY;

			// ������ �̴ϸ� ���� ��ġ ���
			float miniMapX = (unitX * 161.f) / 4096.f;
			float miniMapY = (unitY * 166.f) / 4096.f;

			int screenX = 8 + static_cast<int>(miniMapX);
			int screenY = 430 + static_cast<int>(miniMapY);

			// �簢���� ũ�⸦ �����մϴ�.
			int rectSize = 8;

			COLORREF color;

			if (staticIter->Get_FactionState() == FACTION_ALLY)
			{
				// �ʷϻ� �귯�� ����
				color = RGB(0, 255, 0); // �ʷϻ�
			}
			else if (staticIter->Get_FactionState() == FACTION_ENEMY)
			{
				// ������ �귯�� ����
				color = RGB(255, 0, 0); // ������
			}

			// �簢�� �׸���
			HBRUSH hBrush = CreateSolidBrush(color); // �������� �귯�� ����
			HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			// �簢�� �׸��� (�̴ϸ� ���� ���� ��ġ��)
			Rectangle(hDC, screenX, screenY, screenX + rectSize, screenY + rectSize);

			// ����
			SelectObject(hDC, hOldBrush); // ���� �귯�÷� ����
			DeleteObject(hBrush); // ����� �귯�� ����
		}
	}

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hCurrentDC = CBmpMgr::Get_Instance()->Find_Image(L"MiniMapCurrent");
	GdiTransparentBlt(
		hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		8 + (abs(iScrollX) * 161.f) / 4096.f, // ���� ���� ��ġ ��ǥ
		430 + (abs(iScrollY) * 172.f) / 4096.f,
		29,	// ���� ���� �̹����� ����, ����
		16,
		hCurrentDC,		// ��Ʈ���� ������ �ִ� DC
		0,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		0,
		29,	// ����� ��Ʈ�� ����
		16,	// ����� ��Ʈ�� ����
		RGB(0, 0, 0));	// ������ ���� ��
}

void CUI_MiniMap::Release()
{
}

UIOBJECTTYPE CUI_MiniMap::GetType() const
{
	return UIOBJECTTYPE();
}

int CUI_MiniMap::GetDetailType() const
{
	return 0;
}
