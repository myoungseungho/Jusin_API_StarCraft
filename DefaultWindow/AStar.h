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
	int x, y; // ����� ��ġ
	double cost; // ���� ���κ����� ��� g(n), �Ǽ������� ����
	double heuristic; // �޸���ƽ ��� h(n)
	Node(int x, int y, double c, double h) : x(x), y(y), cost(c), heuristic(h) {} // �����ڵ� ����
	double f() const { return cost + heuristic; } // f(n) = g(n) + h(n), ��ȯ Ÿ�� ����
};

// ��� �񱳸� ���� �Լ� ��ü
struct CompareNode {
	bool operator()(const Node& a, const Node& b) {
		return a.f() > b.f();
	}
};