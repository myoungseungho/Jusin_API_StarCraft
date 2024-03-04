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

// 옥타일 거리 계산 함수
double CAStarMgr::OctileDistance(int x1, int y1, int x2, int y2) {
	int dx = abs(x1 - x2);
	int dy = abs(y1 - y2);
	return sqrt(2) * min(dx, dy) + abs(dx - dy); // 대각선 이동 후 남은 직선 이동
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
		return false;
	}
	return true; // 대각선 이동 가능
}



list<pair<int, int>> CAStarMgr::AStarSearch(const pair<int, int>& start, const pair<int, int>& goal)
{
	//각 노드까지의 시작점으로부터 총 비용 저장
	//초기값은 무한대로 설정하고 아직 방문하지 않은 노드들
	vector<vector<double>> gScore(m_MapSize, vector<double>(m_MapSize, numeric_limits<double>::infinity()));
	//최적 경로를 추적하기 위해 각 노드에 도달하기 직전 방문한 노드 위치 저장
	//초기값은 모두 -1,-1로 설정해 어떤 노드에서도 오지 않았음을 나타냄
	vector<vector<pair<int, int>>> cameFrom(m_MapSize, vector<pair<int, int>>(m_MapSize, { -1, -1 }));
	//이미 평가가 완료된 노드들의 집합. 노드가 평가되면 해당 위치의 값이 TRUE로 평가
	vector<vector<bool>> closedSet(m_MapSize, vector<bool>(m_MapSize, false));
	//아직 평가되지 않았지만 방문할 예정인 노드들의 집합
	priority_queue<Node, vector<Node>, CompareNode> openSet; // 평가할 노드의 우선순위 큐

	//시작 노드 추가
	openSet.push(Node(start.first, start.second, 0, OctileDistance(start.first, start.second, goal.first, goal.second)));
	//시작 노드의 gScore는 0으로 설정
	gScore[start.first][start.second] = 0;

	//방문할 노드가 남아있는 동안 반복 실행
	while (!openSet.empty()) {
		Node current = openSet.top();
		openSet.pop();

		// 목적지에 도달했는지 확인
		if (current.x == goal.first && current.y == goal.second) {
			list<pair<int, int>> path;
			while (!(current.x == start.first && current.y == start.second)) {
				path.push_back({ current.x, current.y });
				auto parent = cameFrom[current.x][current.y];
				current.x = parent.first;
				current.y = parent.second;
			}
			path.push_back({ start.first, start.second }); // 시작점 추가
			reverse(path.begin(), path.end()); // 경로 뒤집기
			return path;
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
	//각 노드까지의 시작점으로부터 총 비용 저장
	//초기값은 무한대로 설정하고 아직 방문하지 않은 노드들
	vector<vector<double>> gScore(m_MapSize, vector<double>(m_MapSize, numeric_limits<double>::infinity()));
	//최적 경로를 추적하기 위해 각 노드에 도달하기 직전 방문한 노드 위치 저장
	//초기값은 모두 -1,-1로 설정해 어떤 노드에서도 오지 않았음을 나타냄
	vector<vector<pair<int, int>>> cameFrom(m_MapSize, vector<pair<int, int>>(m_MapSize, { -1, -1 }));
	//이미 평가가 완료된 노드들의 집합. 노드가 평가되면 해당 위치의 값이 TRUE로 평가
	vector<vector<bool>> closedSet(m_MapSize, vector<bool>(m_MapSize, false));
	//아직 평가되지 않았지만 방문할 예정인 노드들의 집합
	priority_queue<Node, vector<Node>, CompareNode> openSet; // 평가할 노드의 우선순위 큐

	//시작 노드 추가
	openSet.push(Node(start.first, start.second, 0, OctileDistance(start.first, start.second, goal.first, goal.second)));
	//시작 노드의 gScore는 0으로 설정
	gScore[start.first][start.second] = 0;

	//방문할 노드가 남아있는 동안 반복 실행
	while (!openSet.empty()) {
		Node current = openSet.top();
		openSet.pop();

		// 목적지에 도달했는지 확인
		if (current.x == goal.first && current.y == goal.second) {
			list<pair<int, int>> path;
			while (!(current.x == start.first && current.y == start.second)) {
				path.push_back({ current.x, current.y });
				auto parent = cameFrom[current.x][current.y];
				current.x = parent.first;
				current.y = parent.second;
			}
			path.push_back({ start.first, start.second }); // 시작점 추가
			reverse(path.begin(), path.end()); // 경로 뒤집기
			return path;
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
