#include <iostream>
#include <queue>
#include <cstring>

#define MAX_MAP 71
#define WALL -1
#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define EXIT 99999
using namespace std;

struct Point {
	int y;
	int x;
};

struct Golem {
	Point p;
	int num;
};

// 북-동-남-서
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };
int R, C, K;
int map[MAX_MAP + 3][MAX_MAP + 3]; // 골렘이 누적되는 맵
int visited[MAX_MAP + 3][MAX_MAP + 3]; // BFS 방문처리
int ans;

void Input();

Point MoveGolem(Point mp, int exit_dir, int num);
bool CheckMove(Point cp, int dir);
int MoveSoul(Point sp, int num);
void Print();

int main() {
	Input();

	int num = 1;
	Point gp;
	int c, d;
	for (int i = 0; i < K; i++)
	{
		cin >> c >> d;
		gp = MoveGolem({ 1, c }, d, num);
		if (gp.y != -1) {
			ans += MoveSoul(gp, num);
		}
		else {
			num = 1;
		}
		num++;
	}
	cout << ans << '\n';
	
	return 0;

}

void Input() {
	cin >> R >> C >> K;
}

Point MoveGolem(Point mp, int exit_dir, int num) {
	Point cp = mp;
	Point np;
	// 이동을 한 적이 있는지 체크
	// 더 이상 이동할 수 없을때까지 반복해야 하니까
	int flag = true;
	while (flag) {
		flag = false;
		// 1. 남쪽으로 이동
		np = { cp.y + dy[DOWN], cp.x + dx[DOWN] };
		if (CheckMove(np, DOWN)) {
			cp = np;
			flag = true;
		}
		if (!flag) {
			// 2. 서쪽으로 내려가기
			np = { cp.y + dy[LEFT], cp.x + dx[LEFT] };
			if (CheckMove(np, LEFT)) {
				np = { np.y + dy[DOWN], np.x + dx[DOWN] };
				if (CheckMove(np, DOWN)) {
					cp = np;
					// 출구방향 바꿔주기
					exit_dir = (exit_dir - 1 + 4) % 4;
					flag = true;
				}
			}
		}
		if (!flag) {
			// 3. 동쪽으로 내려가기
			np = { cp.y + dy[RIGHT], cp.x + dx[RIGHT] };
			if (CheckMove(np, RIGHT)) {
				np = { np.y + dy[DOWN], np.x + dx[DOWN] };
				if (CheckMove(np, DOWN)) {
					cp = np;
					// 출구방향 바꿔주기
					// 출구방향 바꿔주기
					exit_dir = (exit_dir + 1) % 4;
					flag = true;
				}
			}
		}
		
	}
	
	// 골렘의 위치를 정했다
	// 맵에 표시
	if (cp.y <= 3) {
		// 골렘 몸이 삐져나옴
		// 맵 초기화
		memset(map, 0, sizeof(map));
		return { -1,-1 };
	}
	else {
		// 골렘 표시
		map[cp.y][cp.x] = num;
		for (int d = 0; d < 4; d++)
		{
			np = { cp.y + dy[d], cp.x + dx[d] };
			if (d == exit_dir)
				map[np.y][np.x] = EXIT - num;
			else
				map[np.y][np.x] = num;
		}
	}
	return cp;
}

bool CheckMove(Point cp, int dir) {
	Point np;
	for (int d = 0; d < 4; d++)
	{
		// 반대 방향은 검사 안해도 됨
		if (d == (dir + 2) % 4)
			continue;
		np = { cp.y + dy[d], cp.x + dx[d] };
		// 경계조건
		if (np.y < 0 || np.y >= R + 3 || np.x <= 0 || np.x >= C + 1)
			return false;
		else if (map[np.y][np.x] > 0) // 다른 골렘
			return false;
	}
	return true;
}

void Print() {
	cout << '\n';
	for (int i = 0; i < R+4; i++)
	{
		for (int j = 0; j < C+2; j++)
		{
			cout << map[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
	cout << '\n';
	for (int i = 0; i < R + 4; i++)
	{
		for (int j = 0; j < C + 2; j++)
		{
			cout << visited[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
}

int MoveSoul(Point sp, int num) {
	memset(visited, 0, sizeof(visited));

	queue<Golem> q;
	q.push({sp, num});
	visited[sp.y][sp.x] = 1;

	Golem cp, np; // Point 구조체로 큐를 돌리면 안됨
	while (!q.empty()) {
		cp = q.front();
		q.pop();

		for (int d = 0; d < 4; d++)
		{
			np = { cp.p.y + dy[d], cp.p.x + dx[d], cp.num};
			if (visited[np.p.y][np.p.x] > 0)
				continue;
			if (np.p.y < 0 || np.p.y >= R + 3 || np.p.x <= 0 || np.p.x >= C + 1)
				continue; 
			if (map[np.p.y][np.p.x] == 0)
				continue;
			if (map[np.p.y][np.p.x] == cp.num || map[np.p.y][np.p.x] == EXIT - cp.num) {
				visited[np.p.y][np.p.x] = visited[cp.p.y][cp.p.x] + 1;
				q.push(np);
			}
			// 다른 숫자야 -> 다른 골렘이거나, 다른 골렘의 출구이거나
			else if(map[np.p.y][np.p.x] > 0) {
				if (map[cp.p.y][cp.p.x] == EXIT - cp.num) {
					visited[np.p.y][np.p.x] = visited[cp.p.y][cp.p.x] + 1;

					if (map[np.p.y][np.p.x] > 1000)
						np.num = EXIT - map[np.p.y][np.p.x];
					else
						np.num = map[np.p.y][np.p.x];

					q.push(np);
					
				}
			}
		}
	}

	for (int i = R+3; i >= 3; i--)
	{
		for (int j = 1; j <= C+1; j++)
		{
			if (visited[i][j] > 0)
				return i - 2;
		}
	}
	return 0;
}