#include "stdafx.h"
#include "AStarMgr.h"
#include "TileMgr.h"

CAStarMgr* CAStarMgr::m_pInstance = nullptr;

CAStarMgr::CAStarMgr()
{
}

CAStarMgr::~CAStarMgr()
{
}


void CAStarMgr::Initialize()
{
	Init_ObstacleTile();
}

// ��Ÿ�� �Ÿ� ��� �Լ�
double CAStarMgr::OctileDistance(int x1, int y1, int x2, int y2) {
	int dx = abs(x1 - x2);
	int dy = abs(y1 - y2);
	return sqrt(2) * min(dx, dy) + abs(dx - dy); // �밢�� �̵� �� ���� ���� �̵�
}

void CAStarMgr::Init_ObstacleTile()
{
	for (size_t i = 0; i < m_MapSize; i++)
	{
		vector<bool> row;
		for (size_t j = 0; j < m_MapSize; j++)
		{
			row.push_back(false);
		}

		m_Obstacles.push_back(row);
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
	}
	return true; // �밢�� �̵� ����
}



bool CAStarMgr::AStarSearch(const pair<int, int>& start, const pair<int, int>& goal, int n, const vector<vector<bool>>& obstacles)
{
	vector<vector<pair<int, int>>> cameFrom(n, vector<pair<int, int>>(n, { -1, -1 })); // �θ� ��� ����
	vector<vector<bool>> closedSet(n, vector<bool>(n, false)); // �̹� ���� ��� ����
	priority_queue<Node, vector<Node>, CompareNode> openSet; // ���� ����� �켱���� ť

	openSet.push(Node(start.first, start.second, 0, OctileDistance(start.first, start.second, goal.first, goal.second)));

	while (!openSet.empty()) {
		Node current = openSet.top();
		openSet.pop();

		// �������� �����ߴ��� Ȯ��
		if (current.x == goal.first && current.y == goal.second) {
			vector<pair<int, int>> path;
			while (!(current.x == start.first && current.y == start.second)) {
				path.push_back({ current.x, current.y });
				auto parent = cameFrom[current.x][current.y];
				current.x = parent.first;
				current.y = parent.second;
			}
			path.push_back({ start.first, start.second }); // ������ �߰�
			reverse(path.begin(), path.end()); // ��� ������
			// ��� ���
			for (const auto& p : path) {
				cout << "(" << p.first << ", " << p.second << ") ";
			}
			cout << "Goal reached with cost: " << current.cost << endl;
			return true;
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

			if (nextX >= 0 && nextX < n && nextY >= 0 && nextY < n && !closedSet[nextX][nextY] && !obstacles[nextX][nextY]) {
				if (CanMoveDiagonally(obstacles, current.x, current.y, nextX, nextY)) { // �밢�� �̵� �������� �߰� �˻�
					double nextCost = current.cost + moveCost;
					double nextHeuristic = OctileDistance(nextX, nextY, goal.first, goal.second);
					openSet.push(Node(nextX, nextY, nextCost, nextHeuristic));
					cameFrom[nextX][nextY] = { current.x, current.y }; // �θ� ��� ������Ʈ
				}
			}
		}
	}
	return false;
}

//int main() {
//	pair<int, int> start(0, 0); // �������
//	pair<int, int> goal(3, 3); // ������
//	int n = 4; // ���� ũ��
//
//	// ��ֹ� ���� /*(n, vector<bool>(n, false));*/
//	vector<vector<bool>> obstacles;
//
//	for (size_t i = 0; i < n; i++)
//	{
//		vector<bool> row;
//		for (size_t j = 0; j < n; j++)
//		{
//			row.push_back(false);
//		}
//
//		obstacles.push_back(row);
//	}
//
//	obstacles[1][1] = true;
//	obstacles[2][2] = true;
//
//	AStarSearch(start, goal, n, obstacles);
//
//	return 0;
//}