#include <iostream>
#include <queue>
#include <cstring>

#define MAX_MAP 20
using namespace std;

struct Point {
	int y;
	int x;
};

// 상우하좌 - 시계방향
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

int n, m;
int map[MAX_MAP][MAX_MAP];
int visited[MAX_MAP][MAX_MAP];
// 주사위 아랫면 == dice[2][1]
int dice[4][3] = {
	{0,1,0},
	{0,5,0},
	{4,6,3},
	{0,2,0}
};

int ans;

void Input();
void Simulation();
void RollingDice(int dir); 
int CalcScore(Point sp);

int main() {
	Input();
	Simulation();

	cout << ans << '\n';
	return 0;
}

void Input() {
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> map[i][j];
		}
	}
}

void Simulation() {
	Point p = { 0,0 };
	int dir = 1;

	for (int i = 0; i < m; i++)
	{
		RollingDice(dir);
		p = { p.y + dy[dir], p.x + dx[dir] };

		// 1. 맵 밖으로 간 경우 : 반대방향으로 향하고 한 칸 전진
		if (p.y < 0 || p.y >= n || p.x < 0 || p.x >= n) {
			p = { p.y - 2 * dy[dir], p.x - 2 * dx[dir] };
			dir = (dir + 2 + 4) % 4;
			RollingDice(dir);
			RollingDice(dir);
		}
		// 2. 아닌 경우 : dir 업데이트
		else {
			if (dice[2][1] > map[p.y][p.x]) dir = (dir + 4 + 1) % 4;
			else if (dice[2][1] < map[p.y][p.x]) dir = (dir + 4 - 1) % 4;
			// 같으면 그냥 전진
		}

		ans += CalcScore(p);
	}
}

void RollingDice(int dir) {
	int tmp;
	// 상
	if (dir == 0) {
		tmp = dice[3][1];
		dice[3][1] = dice[2][1];
		dice[2][1] = dice[1][1];
		dice[1][1] = dice[0][1];
		dice[0][1] = tmp;
	}
	// 우
	else if (dir == 1) {
		tmp = dice[2][2];
		dice[2][2] = dice[0][1];
		dice[0][1] = dice[2][0];
		dice[2][0] = dice[2][1];
		dice[2][1] = tmp;
	}
	// 하
	else if (dir == 2) {
		tmp = dice[0][1];
		dice[0][1] = dice[1][1];
		dice[1][1] = dice[2][1];
		dice[2][1] = dice[3][1];
		dice[3][1] = tmp;
	}
	// 좌
	else {
		tmp = dice[2][0];
		dice[2][0] = dice[0][1];
		dice[0][1] = dice[2][2];
		dice[2][2] = dice[2][1];
		dice[2][1] = tmp;
	}
}

int CalcScore(Point sp) {
	memset(visited, 0, sizeof(visited));
	int rst = map[sp.y][sp.x];

	queue<Point> q;
	q.push(sp);
	visited[sp.y][sp.x] = 1;

	Point cp, np;
	while (!q.empty()) {
		cp = q.front();
		q.pop();

		for (int d = 0; d < 4; d++)
		{
			np = { cp.y + dy[d], cp.x + dx[d] };
			if (np.y < 0 || np.y >= n || np.x < 0 || np.x >= n) continue;
			if (visited[np.y][np.x] == 1) continue;
			if (map[np.y][np.x] != map[sp.y][sp.x]) continue;

			visited[np.y][np.x] = 1;
			q.push(np);

			rst += map[np.y][np.x];
		}
	}

	return rst;
}