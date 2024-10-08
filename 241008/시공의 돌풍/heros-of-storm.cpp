#include <iostream>
#include <vector>

#define MAX_MAP 50
using namespace std;

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

int n, m;
int t;
vector<int> map[MAX_MAP][MAX_MAP];
int storm_y, storm_x; // 아래쪽 위치임
int ans;

void Input();
void Simulation();
void SpreadDust();
void CleanDust();
void output();

int main() {
	Input();
	Simulation();
	output();

	return 0;
}

void Input() {
	cin >> n >> m >> t;
	int tmp;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> tmp;
			map[i][j].push_back(tmp);
			if (map[i][j][0] == -1) {
				storm_y = i;
				storm_x = j;
			}
		}
	}
}

void Simulation() {
	for (int i = 0; i < t; i++)
	{
		SpreadDust();
		CleanDust();
	}

}
void SpreadDust() {
	int ny, nx, amount;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (map[i][j][0] == -1) continue;
			amount = map[i][j][0] / 5;
			for (int d = 0; d < 4; d++)
			{
				ny = i + dy[d];
				nx = j + dx[d];
				if (ny < 0 || ny >= n || nx < 0 || nx >= m) continue;
				if (map[ny][nx][0] == -1) continue;
				map[ny][nx].push_back(amount);
				map[i][j][0] -= amount;
			}
		}
	}

	// 달아놓은 먼지 다 합쳐주기
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (map[i][j][0] == -1) continue;

			while (map[i][j].size() != 1) {
				map[i][j][0] += map[i][j][map[i][j].size()-1];
				map[i][j].pop_back();
			}
		}
	}
}

void CleanDust() {
	// 위쪽 - counter_clockwise
	// 하
	int ny, nx;
	int cy = storm_y - 2 - 1;
	int cx = storm_x;
	while (cy > -1) {
		ny = cy + dy[1];
		nx = cx + dx[1];
		map[ny][nx][0] = map[cy][cx][0];
		cy--;
	}
	// 좌
	cy++;
	cx++;
	while (cx < m) {
		ny = cy + dy[2];
		nx = cx + dx[2];
		map[ny][nx][0] = map[cy][cx][0];
		cx++;
	}
	// 상
	cy++;
	cx--;
	while (cy <= storm_y - 1) {
		ny = cy + dy[0];
		nx = cx + dx[0];
		map[ny][nx][0] = map[cy][cx][0];
		cy++;
	}
	//우
	cy--;
	cx--;
	while (cx >= 1) {
		ny = cy + dy[3];
		nx = cx + dx[3];
		map[ny][nx][0] = map[cy][cx][0];
		cx--;
	}
	map[cy][1][0] = 0;

	// 아래쪽 - clockwise
	// 상
	cy = storm_y + 2;
	cx = storm_x;
	while (cy < n) {
		ny = cy + dy[0];
		nx = cx + dx[0];
		map[ny][nx][0] = map[cy][cx][0];
		cy++;
	}
	// 좌
	cy--;
	cx++;
	while (cx < m) {
		ny = cy + dy[2];
		nx = cx + dx[2];
		map[ny][nx][0] = map[cy][cx][0];
		cx++;
	}
	//하
	cy--;
	cx--;
	while (cy >= storm_y) {
		ny = cy + dy[1];
		nx = cx + dx[1];
		map[ny][nx][0] = map[cy][cx][0];
		cy--;
	}
	//우
	cy++;
	cx--;
	while (cx >= 1) {
		ny = cy + dy[3];
		nx = cx + dx[3];
		map[ny][nx][0] = map[cy][cx][0];
		cx--;
	}
	map[cy][1][0] = 0;
}

void output() {
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (map[i][j][0] == -1) continue;
			ans += map[i][j][0];
		}
	}

	cout << ans << '\n';
}