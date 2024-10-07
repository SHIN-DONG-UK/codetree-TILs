#include <iostream>

#define MAX_LEN 50
using namespace std;

int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

int N, M;
int pos_y, pos_x, dir;
int MAP[MAX_LEN][MAX_LEN];
int visited[MAX_LEN][MAX_LEN];
int ans_cnt;

void input();
void simulation();
int turn_left(int dir);

int main() {
	input();
	simulation();

	cout << ans_cnt << '\n';
}

void input() {
	cin >> N >> M;
	cin >> pos_y >> pos_x >> dir;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> MAP[i][j];
		}
	}
}

int turn_left(int dir) {
	return (dir + 4 - 1) % 4;
}

void simulation() {
	ans_cnt++;
	visited[pos_y][pos_x] = 1;

	while (true) {
		int ny = pos_y;
		int nx = pos_x;
		int flag = 0;
		// 1. 4방향 탐색 및 전진
		for (int i = 0; i < 4; i++)
		{
			dir = turn_left(dir);
			ny = pos_y + dy[dir];
			nx = pos_x + dx[dir];
			if (MAP[ny][nx] == 0 && visited[ny][nx] == 0) {
				visited[ny][nx] = 1;
				pos_y = ny; pos_x = nx;
				ans_cnt++;
				flag = 1;
				break;
			}
		}

		// 2. 후진
		if (flag == 0) {
			pos_y -= dy[dir];
			pos_x -= dx[dir];
			if (MAP[pos_y][pos_x] == 1) break;
		}
	}
}