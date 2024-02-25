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
		// 타일의 인덱스 계산
		int index = y * TILEX + x;
		// 인덱스를 사용하여 전체 타일 벡터에서 해당 타일을 추출
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

	// 사각형이 걸치는 타일의 가로, 세로 인덱스 범위 계산
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

	MessageBox(g_hWnd, _T("Save 완료"), L"성공", MB_OK);
}

void CTileMgr::Load_Tile()
{
	HANDLE	hFile = CreateFile(L"../Data/Tile.dat", // 파일 경로(이름을 명시)
		GENERIC_READ,		// 파일 접근 모드 (GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
		NULL,				// 공유 방식, 파일이 열려 있는 상태에서 다른 프로세스가 오픈할 때 허용할 지 여부
		NULL,				// 보안 속성, NULL일 경우 기본 설정 사용
		OPEN_EXISTING,		// CREATE_ALWAYS : 파일이 없다면 생성, 있다면 덮어쓰기, OPEN_EXISTING : 파일이 있을 경우에만 연다
		FILE_ATTRIBUTE_NORMAL,	// 파일 속성, 아무런 속성이 없는 파일을 생성
		NULL);				// 생성될 파일의 속성을 제공할 템플릿 파일

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
	MessageBox(g_hWnd, _T("Load 완료"), L"성공", MB_OK);
}
