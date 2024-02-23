#pragma once
class CAStar
{
public:
	CAStar();
	~CAStar();
public:
	bool AStarSearch(const pair<int, int>& start, const pair<int, int>& goal, int n, const vector<vector<bool>>& obstacles);
	bool CanMoveDiagonally(const vector<vector<bool>>& obstacles, int currentX, int currentY, int nextX, int nextY);
	double OctileDistance(int x1, int y1, int x2, int y2);
};

struct Node {
	int x, y; // 노드의 위치
	double cost; // 시작 노드로부터의 비용 g(n), 실수형으로 변경
	double heuristic; // 휴리스틱 비용 h(n)
	Node(int x, int y, double c, double h) : x(x), y(y), cost(c), heuristic(h) {} // 생성자도 변경
	double f() const { return cost + heuristic; } // f(n) = g(n) + h(n), 반환 타입 변경
};

// 노드 비교를 위한 함수 객체
struct CompareNode {
	bool operator()(const Node& a, const Node& b) {
		return a.f() > b.f();
	}
};