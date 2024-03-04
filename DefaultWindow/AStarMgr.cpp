#include "stdafx.h"
#include "AStarMgr.h"
#include "TileMgr.h"

CAStarMgr* CAStarMgr::m_pInstance = nullptr;

CAStarMgr::CAStarMgr() :m_bInit(true)
{
}

CAStarMgr::~CAStarMgr()
{
	Release();
}


void CAStarMgr::Initialize()
{
	Init_ObstacleTile();
}

void CAStarMgr::Release()
{

}

// ��Ÿ�� �Ÿ� ��� �Լ�
double CAStarMgr::OctileDistance(int x1, int y1, int x2, int y2) {
	int dx = abs(x1 - x2);
	int dy = abs(y1 - y2);
	return sqrt(2) * min(dx, dy) + abs(dx - dy); // �밢�� �̵� �� ���� ���� �̵�
}

void CAStarMgr::Init_ObstacleTile()
{
	if (m_bInit == true)
	{
		m_Obstacles.reserve(128);
		for (size_t i = 0; i < m_MapSize; i++)
		{
			vector<bool> row;
			row.reserve(128);
			for (size_t j = 0; j < m_MapSize; j++)
			{
				row.push_back(false);
			}

			m_Obstacles.push_back(row);
		}

		m_bInit = false;
	}

	//��ֹ� Ÿ�� �ε�
	vector<CObj*> obstcalesTile = CTileMgr::Get_Instance()->GetVecObstcales();

	for (auto iter : obstcalesTile)
	{
		int x = iter->Get_Info().fX / TILECX;
		int y = iter->Get_Info().fY / TILECY;

		m_Obstacles[x][y] = true;
	}
}

// �밢�� �̵��� �������� Ȯ���ϴ� �Լ�
bool CAStarMgr::CanMoveDiagonally(const vector<vector<bool>>& obstacles, int currentX, int currentY, int nextX, int nextY) {
	if (abs(currentX - nextX) == 1 && abs(currentY - nextY) == 1) { // �밢�� �̵��� ���
		// �밢�� �̵� ��ο� ��ֹ��� �ִ��� Ȯ��
		if (obstacles[currentX][nextY] || obstacles[nextX][currentY]) {
			return false; // ��ֹ��� ������ �̵� �Ұ�
		}
		return false;
	}
	return true; // �밢�� �̵� ����
}



list<pair<int, int>> CAStarMgr::AStarSearch(const pair<int, int>& start, const pair<int, int>& goal)
{
	//�� �������� ���������κ��� �� ��� ����
	//�ʱⰪ�� ���Ѵ�� �����ϰ� ���� �湮���� ���� ����
	vector<vector<double>> gScore(m_MapSize, vector<double>(m_MapSize, numeric_limits<double>::infinity()));
	//���� ��θ� �����ϱ� ���� �� ��忡 �����ϱ� ���� �湮�� ��� ��ġ ����
	//�ʱⰪ�� ��� -1,-1�� ������ � ��忡���� ���� �ʾ����� ��Ÿ��
	vector<vector<pair<int, int>>> cameFrom(m_MapSize, vector<pair<int, int>>(m_MapSize, { -1, -1 }));
	//�̹� �򰡰� �Ϸ�� ������ ����. ��尡 �򰡵Ǹ� �ش� ��ġ�� ���� TRUE�� ��
	vector<vector<bool>> closedSet(m_MapSize, vector<bool>(m_MapSize, false));
	//���� �򰡵��� �ʾ����� �湮�� ������ ������ ����
	priority_queue<Node, vector<Node>, CompareNode> openSet; // ���� ����� �켱���� ť

	//���� ��� �߰�
	openSet.push(Node(start.first, start.second, 0, OctileDistance(start.first, start.second, goal.first, goal.second)));
	//���� ����� gScore�� 0���� ����
	gScore[start.first][start.second] = 0;

	//�湮�� ��尡 �����ִ� ���� �ݺ� ����
	while (!openSet.empty()) {
		Node current = openSet.top();
		openSet.pop();

		// �������� �����ߴ��� Ȯ��
		if (current.x == goal.first && current.y == goal.second) {
			list<pair<int, int>> path;
			while (!(current.x == start.first && current.y == start.second)) {
				path.push_back({ current.x, current.y });
				auto parent = cameFrom[current.x][current.y];
				current.x = parent.first;
				current.y = parent.second;
			}
			path.push_back({ start.first, start.second }); // ������ �߰�
			reverse(path.begin(), path.end()); // ��� ������
			return path;
		}

		closedSet[current.x][current.y] = true; // ���� ��带 ��� ���տ� �߰�

		// ���� ��� Ž��: ��, ��, ��, �� + �밢��
		vector<pair<int, int>> directions = {
			{1, 0}, {0, 1}, {-1, 0}, {0, -1}, // ��, ��, ��, ��
			{1, 1}, {-1, 1}, {1, -1}, {-1, -1} }; // �밢��    
		for (const auto& dir : directions) {
			int nextX = current.x + dir.first;
			int nextY = current.y + dir.second;

			// �밢�� �̵� ����� �ٸ��� ����
			double moveCost = (dir.first == 0 || dir.second == 0) ? 1.0 : sqrt(2);

			if (nextX >= 0 && nextX < m_MapSize && nextY >= 0 && nextY < m_MapSize && !m_Obstacles[nextX][nextY]) {
				double tentative_gScore = gScore[current.x][current.y] + moveCost;
				if (tentative_gScore < gScore[nextX][nextY]) {
					cameFrom[nextX][nextY] = { current.x, current.y };
					gScore[nextX][nextY] = tentative_gScore;
					double nextHeuristic = OctileDistance(nextX, nextY, goal.first, goal.second);
					if (!closedSet[nextX][nextY]) {
						openSet.push(Node(nextX, nextY, tentative_gScore, nextHeuristic));
					}
				}
			}
		}
	}

	return list<pair<int, int>>();
}


list<pair<int, int>> CAStarMgr::SCV_AStarSearch(const pair<int, int>& start, const pair<int, int>& goal)
{
	//�� �������� ���������κ��� �� ��� ����
	//�ʱⰪ�� ���Ѵ�� �����ϰ� ���� �湮���� ���� ����
	vector<vector<double>> gScore(m_MapSize, vector<double>(m_MapSize, numeric_limits<double>::infinity()));
	//���� ��θ� �����ϱ� ���� �� ��忡 �����ϱ� ���� �湮�� ��� ��ġ ����
	//�ʱⰪ�� ��� -1,-1�� ������ � ��忡���� ���� �ʾ����� ��Ÿ��
	vector<vector<pair<int, int>>> cameFrom(m_MapSize, vector<pair<int, int>>(m_MapSize, { -1, -1 }));
	//�̹� �򰡰� �Ϸ�� ������ ����. ��尡 �򰡵Ǹ� �ش� ��ġ�� ���� TRUE�� ��
	vector<vector<bool>> closedSet(m_MapSize, vector<bool>(m_MapSize, false));
	//���� �򰡵��� �ʾ����� �湮�� ������ ������ ����
	priority_queue<Node, vector<Node>, CompareNode> openSet; // ���� ����� �켱���� ť

	//���� ��� �߰�
	openSet.push(Node(start.first, start.second, 0, OctileDistance(start.first, start.second, goal.first, goal.second)));
	//���� ����� gScore�� 0���� ����
	gScore[start.first][start.second] = 0;

	//�湮�� ��尡 �����ִ� ���� �ݺ� ����
	while (!openSet.empty()) {
		Node current = openSet.top();
		openSet.pop();

		// �������� �����ߴ��� Ȯ��
		if (current.x == goal.first && current.y == goal.second) {
			list<pair<int, int>> path;
			while (!(current.x == start.first && current.y == start.second)) {
				path.push_back({ current.x, current.y });
				auto parent = cameFrom[current.x][current.y];
				current.x = parent.first;
				current.y = parent.second;
			}
			path.push_back({ start.first, start.second }); // ������ �߰�
			reverse(path.begin(), path.end()); // ��� ������
			return path;
		}

		closedSet[current.x][current.y] = true; // ���� ��带 ��� ���տ� �߰�

		// ���� ��� Ž��: ��, ��, ��, �� + �밢��
		vector<pair<int, int>> directions = {
			{1, 0}, {0, 1}, {-1, 0}, {0, -1}, // ��, ��, ��, ��
			{1, 1}, {-1, 1}, {1, -1}, {-1, -1} }; // �밢��    
		for (const auto& dir : directions) {
			int nextX = current.x + dir.first;
			int nextY = current.y + dir.second;

			// �밢�� �̵� ����� �ٸ��� ����
			double moveCost = (dir.first == 0 || dir.second == 0) ? 1.0 : sqrt(2);

			if (nextX >= 0 && nextX < m_MapSize && nextY >= 0 && nextY < m_MapSize && !m_Obstacles[nextX][nextY]) {
				double tentative_gScore = gScore[current.x][current.y] + moveCost;
				if (tentative_gScore < gScore[nextX][nextY]) {
					cameFrom[nextX][nextY] = { current.x, current.y };
					gScore[nextX][nextY] = tentative_gScore;
					double nextHeuristic = OctileDistance(nextX, nextY, goal.first, goal.second);
					if (!closedSet[nextX][nextY]) {
						openSet.push(Node(nextX, nextY, tentative_gScore, nextHeuristic));
					}
				}
			}

			if (nextX == goal.first && nextY == goal.second)
			{
				double tentative_gScore = gScore[current.x][current.y] + moveCost;
				cameFrom[nextX][nextY] = { current.x, current.y };
				gScore[nextX][nextY] = tentative_gScore;
				double nextHeuristic = OctileDistance(nextX, nextY, goal.first, goal.second);
				if (!closedSet[nextX][nextY]) {
					openSet.push(Node(nextX, nextY, tentative_gScore, nextHeuristic));
				}
			}


		}
	}

	return list<pair<int, int>>();
}
