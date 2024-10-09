#include <iostream>
#include <cstring>

#define MAX_MAP 20
using namespace std;

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

int ddy[4] = { -1,1,1,-1 };
int ddx[4] = { 1,1,-1,-1 };

int map[MAX_MAP][MAX_MAP];
int next_map[MAX_MAP][MAX_MAP];
int check[MAX_MAP][MAX_MAP];

int n, m, k, c;

void Input();
void GrowAndReproduce();
int FindMaxAndSpray();
void Decay();
void Simulation();

int main() {
	Input();
	Simulation();

	return 0;

}

void Input() {
	cin >> n >> m >> k >> c;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> map[i][j];
		}
	}
}

void Simulation() {
	int rst = 0;
	for (int i = 0; i < m; i++)
	{
		GrowAndReproduce();
		rst += FindMaxAndSpray();
		Decay();
	}
	
	cout << rst << '\n';
}

void GrowAndReproduce() {
	memset(next_map, 0, sizeof(next_map));

	int ny, nx;
	int cnt;
	int cnt_blank;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (map[i][j] > 0) {
				cnt = 0;
				cnt_blank = 0;
				for (int d = 0; d < 4; d++)
				{
					ny = i + dy[d];
					nx = j + dx[d];
					if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
					if (check[ny][nx] > 0) continue; // 제초제 컽
					if (map[ny][nx] == 0)
						cnt_blank++;
					else if (map[ny][nx] > 0)
						cnt++;
					
				}
				// Grow
				map[i][j] += cnt;

				if (cnt_blank == 0) continue;

				// Reproduce
				for (int d = 0; d < 4; d++)
				{
					ny = i + dy[d];
					nx = j + dx[d];
					if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
					if (check[ny][nx] > 0) continue;
					if (map[ny][nx] == 0) {
						next_map[ny][nx] += map[i][j] / cnt_blank;
					}

				}
			}
		}
	}

	// update reproduce
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			map[i][j] += next_map[i][j];
		}
	}
}

int FindMaxAndSpray() {
	int rst = 0;

	int max_val = 0;
	int max_i = -1;
	int max_j = -1;

	int ny, nx;
	int sum;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (map[i][j] > 0) {
				sum = map[i][j];
				for (int d = 0; d < 4; d++)
				{
					for (int l = 1; l <= k; l++)
					{
						ny = i + ddy[d]*l;
						nx = j + ddx[d]*l;
						if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
						if (map[ny][nx] == -1) break;
						if (map[ny][nx] == 0) break;
						sum += map[ny][nx];
					}
				}
				if (sum > max_val) {
					max_val = sum;
					max_i = i;
					max_j = j;
				}
			}
		}
	}
	// 나무가 없는 케이스도 있을 수 있음
	if (max_val == 0) return rst;
	
	// max_val, max_i, max_j를 아니까, 제초제 표시해줭
	rst += map[max_i][max_j];

	check[max_i][max_j] = c + 1;
	map[max_i][max_j] = 0;

	for (int d = 0; d < 4; d++)
	{
		for (int l = 1; l <= k; l++)
		{
			ny = max_i + ddy[d] * l;
			nx = max_j + ddx[d] * l;
			if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
			if (map[ny][nx] == -1) break;
			if (map[ny][nx] == 0) {
				//check[ny][nx] = c + 1;
				break;
			}
			rst += map[ny][nx];

			check[ny][nx] = c + 1;
			map[ny][nx] = 0;

		}
	}

	return rst;
}
void Decay() {
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (check[i][j] >= 1) check[i][j]--;
		}
	}
}