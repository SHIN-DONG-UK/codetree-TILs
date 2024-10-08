#include <iostream>

#define MAX_MAP 20
#define MAX_CMD 1000
using namespace std;

// 우좌상하
int dy[4] = { 0,0,-1,1 };
int dx[4] = { 1,-1,0,0 };

int n, m, x, y, k;
int dice[4][3];
int map[MAX_MAP][MAX_MAP];
int commands[MAX_CMD];
int ans;

void Input();
void Simulation();
bool RollingDice(int dir); // 정육면체 모양 + 위치 업데이트

int main() {
	Input();
	Simulation();

	return 0;
}

void Input() {
	cin >> n >> m >> y >> x >> k;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < k; i++)
	{
		cin >> commands[i];
		commands[i]--;
	}

}

void Simulation() {
	for (int i = 0; i < k; i++) {
		if (RollingDice(commands[i]))
			cout << dice[0][1] << '\n';
	}
}

bool RollingDice(int dir) {
	int ny = y + dy[dir];
	int nx = x + dx[dir];
	if (ny < 0 || ny >= n || nx < 0 || nx >= m) return false;

	if (dir == 0) {
		int tmp = dice[0][1];
		dice[0][1] = dice[2][0];
		dice[2][0] = dice[2][1];
		dice[2][1] = dice[2][2];
		dice[2][2] = tmp;
	}
	else if (dir == 1) {
		int tmp = dice[0][1];
		dice[0][1] = dice[2][2];
		dice[2][2] = dice[2][1];
		dice[2][1] = dice[2][0];
		dice[2][0] = tmp;
	}
	else if (dir == 2) {
		int tmp = dice[3][1];
		for (int i = 2; i >= 0; i--)
		{
			dice[i + 1][1] = dice[i][1];
		}
		dice[0][1] = tmp;
	}
	else {
		int tmp = dice[0][1];
		for (int i = 1; i < 4; i++)
		{
			dice[i - 1][1] = dice[i][1];
		}
		dice[3][1] = tmp;
	}

	if (map[ny][nx] == 0) {
		map[ny][nx] = dice[2][1];
	}
	else {
		dice[2][1] = map[ny][nx];
		map[ny][nx] = 0;
	}

	y = ny;
	x = nx;

	return true;
}