#pragma once
#include "Define.h"

class CAStarMgr
{
private:
	CAStarMgr();
	~CAStarMgr();
public:
	static		CAStarMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CAStarMgr;

		return m_pInstance;
	}

	static void	Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
public:
	void		Initialize();
	void		Release();

public:
	list<pair<int, int>> AStarSearch(const pair<int, int>& start, const pair<int, int>& goal);
	list<pair<int, int>> SCV_AStarSearch(const pair<int, int>& start, const pair<int, int>& goal);

	bool CanMoveDiagonally(const vector<vector<bool>>& obstacles, int currentX, int currentY, int nextX, int nextY);
	double OctileDistance(int x1, int y1, int x2, int y2);
public:
	int GetMapSize() { return m_MapSize; }
	void Init_ObstacleTile();
private:
	static CAStarMgr* m_pInstance;

	vector<vector<bool>> m_Obstacles;

	int m_MapSize = TILEX; // 맵의 크기
	bool m_bInit;
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