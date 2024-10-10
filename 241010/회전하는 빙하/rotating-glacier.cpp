#include <iostream>
#include <vector>
#include <math.h>
#include <queue>
#include <cstring>

#define MAX_MAP 64
#define MAX_CMD 1000
using namespace std;

int len_map;

struct Point {
	int y;
	int x;
};

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

int n, q;
int map[MAX_MAP][MAX_MAP];
int next_map[MAX_MAP][MAX_MAP];
int visited[MAX_MAP][MAX_MAP];
vector<int> commands;

int ans1;
int ans2;

void Input();
void Simulation();
void RotateIces(int lev);
void MeltIces();
void GetAnswer();
int BFS(Point sp);

void print();

int main() {
	Input();
	Simulation();
	GetAnswer();

	cout << ans1 << '\n';
	cout << ans2 << '\n';

	return 0;
}

void Input() {
	cin >> n >> q;
	len_map = pow(2, n);
	for (int i = 0; i < len_map; i++)
	{
		for (int j = 0; j < len_map; j++)
		{
			cin >> map[i][j];
		}
	}

	int rot;
	for (int i = 0; i < q; i++)
	{
		cin >> rot;
		commands.push_back(rot);
	}
}

void Simulation() {
	for (int i = 0; i < commands.size(); i++)
	{
		RotateIces(commands[i]);
		MeltIces();
	}
}

void RotateIces(int lev) {
	if (lev == 0) return;

	int len_lev = pow(2, lev);
	int len_chunk = pow(2, lev) / 2;

	int B[MAX_MAP][MAX_MAP] = { 0, };

	for (int std_y = 0; std_y < len_map; std_y += len_lev)
	{
		for (int std_x = 0; std_x < len_map; std_x += len_lev)
		{

			for (int std2_y = 0; std2_y < len_lev; std2_y += len_chunk)
			{
				for (int std2_x = 0; std2_x < len_lev; std2_x += len_chunk)
				{

					for (int i = 0; i < len_chunk; i++)
					{
						for (int j = 0; j < len_chunk; j++)
						{
							// 1. 좌표 지정 완료
							// 2. 이제 std_y, std_x를 기준으로 4칸을 회전시킬거다
							// 3. 시계방향 회전
							//		chunck를 회전시키는 거임
							// 그럼 std2가 회전해야 함
							// 
							B[std_y + std2_y + i][std_x + std2_x + j] = map[std_y + i + len_lev - len_chunk - std2_x][std_x + j + std2_y];
						}
					}
				}

			}
			
		}
	}
	for (int i = 0; i < len_map; i++)
	{
		for (int j = 0; j < len_map; j++)
		{
			map[i][j] = B[i][j];
		}
	}

}

void MeltIces() {
	memset(next_map, 0, sizeof(next_map));

	int ny, nx;
	int cnt;
	for (int i = 0; i < len_map; i++)
	{
		for (int j = 0; j < len_map; j++)
		{
			if (map[i][j] == 0)  continue;
			cnt = 0;
			for (int d = 0; d < 4; d++)
			{
				ny = i + dy[d];
				nx = j + dx[d];
				if (ny < 0 || ny >= len_map || nx < 0 || nx >= len_map) {
					cnt++;
					continue;
				}
				if (map[ny][nx] == 0) cnt++;
			}
			if (cnt >= 2) {
				next_map[i][j] -= 1;
			}

		}
	}
	// 원래 맵에 반영
	for (int i = 0; i < len_map; i++)
	{
		for (int j = 0; j < len_map; j++)
		{
			map[i][j] += next_map[i][j];
		}
	}
}


void GetAnswer() {
	for (int i = 0; i < len_map; i++)
	{
		for (int j = 0; j < len_map; j++)
		{
			ans1 += map[i][j];
		}
	}

	int tmp;
	
	for (int i = 0; i < len_map; i++)
	{
		for (int j = 0; j < len_map; j++)
		{
			if (visited[i][j] == 1) continue;
			if (map[i][j] == 0) continue;
			tmp = BFS({ i, j });
			if (tmp > ans2) ans2 = tmp;

		}
	}

}

int BFS(Point sp) {
	queue<Point> q;
	q.push(sp);
	visited[sp.y][sp.x] = 1;

	int cnt = 1;

	Point cp, np;
	while (!q.empty()) {
		cp = q.front();
		q.pop();

		for (int d = 0; d < 4; d++)
		{
			np = { cp.y + dy[d], cp.x + dx[d] };
			if (np.y < 0 || np.y >= len_map | np.x < 0 || np.x >= len_map) continue;
			if (visited[np.y][np.x] == 1) continue;
			if (map[np.y][np.x] == 0) continue;

			visited[np.y][np.x] = 1;
			q.push(np);

			cnt++;
		}
	}
	return cnt;
}

void print() {
	cout << '\n';
	for (int i = 0; i < len_map; i++)
	{
		for (int j = 0; j < len_map; j++)
		{
			cout << map[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
}