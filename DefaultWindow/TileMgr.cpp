#include "stdafx.h"
#include "TileMgr.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"
#include "AStarMgr.h"
CTileMgr* CTileMgr::m_pInstance = nullptr;

CTileMgr::CTileMgr()
{
	m_vecTile.reserve(TILEX * TILEY);
}

CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialize()
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			float	fX = (TILECX >> 1) + float(TILECX * j);
			float	fY = (TILECY >> 1) + float(TILECY * i);

			CObj* pTile = CAbstractFactory<CTile>::Create(fX, fY);
			m_vecTile.push_back(pTile);
		}
	}
}

void CTileMgr::Update()
{
	for (auto& iter : m_vecTile)
		iter->Update();
}

void CTileMgr::Late_Update()
{
	for (auto& iter : m_vecTile)
		iter->Late_Update();
}

void CTileMgr::Render(HDC hDC)
{
	int		iScrollX = abs((int)CScrollMgr::Get_Instance()->Get_ScrollX() / TILECX);
	int		iScrollY = abs((int)CScrollMgr::Get_Instance()->Get_ScrollY() / TILECY);

	int		iMaxX = iScrollX + WINCX / TILECX + 2;
	int		iMaxY = iScrollY + WINCY / TILECY + 2;

	for (int i = iScrollY; i < iMaxY; ++i)
	{
		for (int j = iScrollX; j < iMaxX; ++j)
		{
			int		iIndex = i * TILEX + j;

			if (0 > iIndex || (size_t)iIndex >= m_vecTile.size())
				continue;

			m_vecTile[iIndex]->Render(hDC);
		}
	}

}

void CTileMgr::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<CObj*>);
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}

void CTileMgr::Picking(POINT pt, int _iDrawID, int _iOption)
{
	int	x = pt.x / TILECX;
	int	y = pt.y / TILECY;

	int		iIndex = y * TILEX + x;

	if (0 > iIndex || (size_t)iIndex >= m_vecTile.size())
		return;

	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_Value(_iDrawID, _iOption);
}


list<CObj*> CTileMgr::GetListPath(list<pair<int, int>> _vecPath)
{
	list<CObj*> pathTiles;
	for (const auto& pos : _vecPath) {
		int x = pos.first;
		int y = pos.second;
		// Ÿ���� �ε��� ���
		int index = y * TILEX + x;
		// �ε����� ����Ͽ� ��ü Ÿ�� ���Ϳ��� �ش� Ÿ���� ����
		if (index >= 0 && index < m_vecTile.size()) {
			pathTiles.push_back(m_vecTile[index]);
		}
	}

	return pathTiles;
}

list<CObj*> CTileMgr::GetStaticTile(CObj* _staticObj)
{
	RECT objRect = _staticObj->Get_Rect();
	INFO objInfo = _staticObj->Get_Info();

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	// �簢���� ��ġ�� Ÿ���� ����, ���� �ε��� ���� ���
	int startCol = (objRect.left + iScrollX) / TILECX;
	int endCol = (objRect.right + iScrollX) / TILECX;
	int startRow = (objRect.top + iScrollY) / TILECY;
	int endRow = (objRect.bottom + iScrollY) / TILECY;

	list<CObj*> listTile;

	for (size_t i = startCol; i < endCol; i++)
	{
		for (size_t j = startRow + 1; j < endRow; j++)
		{
			int index = j * TILEX + i;
			if (index >= 0 && index < m_vecTile.size()) {
				listTile.push_back(m_vecTile[index]);
			}
		}
	}

	return listTile;
}

void CTileMgr::SetVecObstcales(list<CObj*> _list)
{
	for (auto iter : _list)
	{
		m_vecObstcales.push_back(iter);
	}

	CAStarMgr::Get_Instance()->Init_ObstacleTile();
}


void CTileMgr::Save_Tile()
{
	HANDLE	hFile = CreateFile(L"../Data/Tile.dat",
		GENERIC_WRITE,
		NULL,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Save File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte(0);
	int		iDrawID(0), iOption(0);

	for (auto& iter : m_vecTile)
	{
		iDrawID = dynamic_cast<CTile*>(iter)->Get_DrawID();
		iOption = dynamic_cast<CTile*>(iter)->Get_Option();

		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, NULL);
		WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);
		WriteFile(hFile, &iOption, sizeof(int), &dwByte, NULL);
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save �Ϸ�"), L"����", MB_OK);
}

void CTileMgr::Load_Tile()
{
	HANDLE	hFile = CreateFile(L"../Data/Tile.dat", // ���� ���(�̸��� ���)
		GENERIC_READ,		// ���� ���� ��� (GENERIC_WRITE : ���� ����, GENERIC_READ : �б� ����)
		NULL,				// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� �� ����
		NULL,				// ���� �Ӽ�, NULL�� ��� �⺻ ���� ���
		OPEN_EXISTING,		// CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING : ������ ���� ��쿡�� ����
		FILE_ATTRIBUTE_NORMAL,	// ���� �Ӽ�, �ƹ��� �Ӽ��� ���� ������ ����
		NULL);				// ������ ������ �Ӽ��� ������ ���ø� ����

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte(0);

	INFO		tInfo{};
	int	iDrawID(0), iOption(0);

	Release();

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, NULL);
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);
		ReadFile(hFile, &iOption, sizeof(int), &dwByte, NULL);

		if (0 == dwByte)
			break;

		CObj* pTile = CAbstractFactory<CTile>::Create(tInfo.fX, tInfo.fY);
		CTile* tile = dynamic_cast<CTile*>(pTile);
		tile->Set_Value(iDrawID, iOption);
		m_vecTile.push_back(pTile);

		if (tile->Get_DrawID() == 1)
		{
			m_vecObstcales.push_back(pTile);
		}
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, _T("Load �Ϸ�"), L"����", MB_OK);
}
