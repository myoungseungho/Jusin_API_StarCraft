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

// 옥타일 거리 계산 함수
double CAStarMgr::OctileDistance(int x1, int y1, int x2, int y2) {
	int dx = abs(x1 - x2);
	int dy = abs(y1 - y2);
	return sqrt(2) * min(dx, dy) + abs(dx - dy); // 대각선 이동 후 남은 직선 이동
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

	//장애물 타일 로드
	vector<CObj*> obstcalesTile = CTileMgr::Get_Instance()->GetVecObstcales();

	for (auto iter : obstcalesTile)
	{
		int x = iter->Get_Info().fX / TILECX;
		int y = iter->Get_Info().fY / TILECY;

		m_Obstacles[x][y] = true;
	}
}

// 대각선 이동이 가능한지 확인하는 함수
bool CAStarMgr::CanMoveDiagonally(const vector<vector<bool>>& obstacles, int currentX, int currentY, int nextX, int nextY) {
	if (abs(currentX - nextX) == 1 && abs(currentY - nextY) == 1) { // 대각선 이동인 경우
		// 대각선 이동 경로에 장애물이 있는지 확인
		if (obstacles[currentX][nextY] || obstacles[nextX][currentY]) {
			return false; // 장애물이 있으면 이동 불가
		}
	}
	return true; // 대각선 이동 가능
}



bool CAStarMgr::AStarSearch(const pair<int, int>& start, const pair<int, int>& goal, int n, const vector<vector<bool>>& obstacles)
{
	vector<vector<pair<int, int>>> cameFrom(n, vector<pair<int, int>>(n, { -1, -1 })); // 부모 노드 추적
	vector<vector<bool>> closedSet(n, vector<bool>(n, false)); // 이미 평가한 노드 집합
	priority_queue<Node, vector<Node>, CompareNode> openSet; // 평가할 노드의 우선순위 큐

	openSet.push(Node(start.first, start.second, 0, OctileDistance(start.first, start.second, goal.first, goal.second)));

	while (!openSet.empty()) {
		Node current = openSet.top();
		openSet.pop();

		// 목적지에 도달했는지 확인
		if (current.x == goal.first && current.y == goal.second) {
			vector<pair<int, int>> path;
			while (!(current.x == start.first && current.y == start.second)) {
				path.push_back({ current.x, current.y });
				auto parent = cameFrom[current.x][current.y];
				current.x = parent.first;
				current.y = parent.second;
			}
			path.push_back({ start.first, start.second }); // 시작점 추가
			reverse(path.begin(), path.end()); // 경로 뒤집기
			// 경로 출력
			for (const auto& p : path) {
				cout << "(" << p.first << ", " << p.second << ") ";
			}
			cout << "Goal reached with cost: " << current.cost << endl;
			return true;
		}

		closedSet[current.x][current.y] = true; // 현재 노드를 폐쇄 집합에 추가

		// 인접 노드 탐색: 상, 하, 좌, 우 + 대각선
		vector<pair<int, int>> directions = {
			{1, 0}, {0, 1}, {-1, 0}, {0, -1}, // 상, 하, 좌, 우
			{1, 1}, {-1, 1}, {1, -1}, {-1, -1} }; // 대각선    
		for (const auto& dir : directions) {
			int nextX = current.x + dir.first;
			int nextY = current.y + dir.second;

			// 대각선 이동 비용을 다르게 적용
			double moveCost = (dir.first == 0 || dir.second == 0) ? 1.0 : sqrt(2);

			if (nextX >= 0 && nextX < n && nextY >= 0 && nextY < n && !closedSet[nextX][nextY] && !obstacles[nextX][nextY]) {
				if (CanMoveDiagonally(obstacles, current.x, current.y, nextX, nextY)) { // 대각선 이동 가능한지 추가 검사
					double nextCost = current.cost + moveCost;
					double nextHeuristic = OctileDistance(nextX, nextY, goal.first, goal.second);
					openSet.push(Node(nextX, nextY, nextCost, nextHeuristic));
					cameFrom[nextX][nextY] = { current.x, current.y }; // 부모 노드 업데이트
				}
			}
		}
	}
	return false;
}

//int main() {
//	pair<int, int> start(0, 0); // 출발지점
//	pair<int, int> goal(3, 3); // 목적지
//	int n = 4; // 맵의 크기
//
//	// 장애물 설정 /*(n, vector<bool>(n, false));*/
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