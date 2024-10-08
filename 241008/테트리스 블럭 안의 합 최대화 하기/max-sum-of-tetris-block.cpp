#include <iostream>

#define BLOCK_LEN 4
#define MAP_LEN 206
using namespace std;

int blocks[5][BLOCK_LEN][BLOCK_LEN] = {
{{1,1,1,1},{0,0,0,0},{0,0,0,0},{0,0,0,0}},
{{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
{{1,0,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}},
{{1,0,0,0},{1,0,0,0},{1,1,0,0},{0,0,0,0}},
{{1,0,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}}
};

int n, m;
int map[MAP_LEN][MAP_LEN];
int ans;

void Input();
void Simulation();
void RotateBlock(int idx);
void FlipUpAndDown(int idx);
void FlipLeftAndRight(int idx);
int CalcSum(int idx, int head_y, int head_x);

int main() {
	Input();
	//Simulation();
	int tmp;
	for (int t = 0; t < 4; t++)
	{
		RotateBlock(3);
		for (int i = 0; i < n + 3; i++)
		{
			for (int j = 0; j < m + 3; j++)
			{
				tmp = CalcSum(3, i, j);
				if (tmp > ans) ans = tmp;
			}
		}

	}
	cout << ans << '\n';
	return 0;
}

void Input() {
	cin >> n >> m;
	for (int i = 3; i < n + 3; i++)
	{
		for (int j = 3; j < m + 3; j++)
		{
			cin >> map[i][j];
		}
	}
}

void Simulation() {
	int tmp = 0;
	for (int idx = 0; idx < 5; idx++)
	{
		for (int t = 0; t < 4; t++)
		{
			RotateBlock(idx);
			for (int i = 0; i < n + 3; i++)
			{
				for (int j = 0; j < m + 3; j++)
				{
					tmp = CalcSum(idx, i, j);
					if (tmp > ans) ans = tmp;
				}
			}

		}
		FlipLeftAndRight(idx);
		for (int t = 0; t < 4; t++)
		{
			RotateBlock(idx);
			for (int i = 0; i < n+3; i++)
			{
				for (int j = 0; j < m+3; j++)
				{
					tmp = CalcSum(idx, i, j);
					if (tmp > ans) ans = tmp;
				}
			}

		}
		FlipLeftAndRight(idx);
		FlipUpAndDown(idx);
		for (int t = 0; t < 4; t++)
		{
			RotateBlock(idx);
			for (int i = 0; i < n + 3; i++)
			{
				for (int j = 0; j < m + 3; j++)
				{
					tmp = CalcSum(idx, i, j);
					if (tmp > ans) ans = tmp;
				}
			}

		}
	}
}

int CalcSum(int idx, int head_y, int head_x) {
	int rst = 0;
	for (int i = 0; i < BLOCK_LEN; i++)
	{
		for (int j = 0; j < BLOCK_LEN; j++)
		{
			rst += map[head_y + i][head_x + j] * blocks[idx][i][j];
		}
	}

	return rst;
}

void RotateBlock(int idx) {
	int tmp_arr[BLOCK_LEN][BLOCK_LEN] = { 0, };
	for (int i = 0; i < BLOCK_LEN; i++)
	{
		for (int j = 0; j < BLOCK_LEN; j++)
		{
			tmp_arr[i][j] = blocks[idx][BLOCK_LEN - j - 1][i];
		}
	}

	for (int i = 0; i < BLOCK_LEN; i++)
	{
		for (int j = 0; j < BLOCK_LEN; j++)
		{
			blocks[idx][i][j] = tmp_arr[i][j];
		}
	}
}

void FlipUpAndDown(int idx) {
	int tmp_arr[BLOCK_LEN][BLOCK_LEN] = { 0, };
	for (int i = 0; i < BLOCK_LEN; i++)
	{
		for (int j = 0; j < BLOCK_LEN; j++)
		{
			tmp_arr[i][j] = blocks[idx][BLOCK_LEN - i - 1][j];
		}
	}
	for (int i = 0; i < BLOCK_LEN; i++)
	{
		for (int j = 0; j < BLOCK_LEN; j++)
		{
			blocks[idx][i][j] = tmp_arr[i][j];
		}
	}
}

void FlipLeftAndRight(int idx) {
	int tmp_arr[BLOCK_LEN][BLOCK_LEN] = { 0, };
	for (int i = 0; i < BLOCK_LEN; i++)
	{
		for (int j = 0; j < BLOCK_LEN; j++)
		{
			tmp_arr[i][j] = blocks[idx][i][BLOCK_LEN - j - 1];
		}
	}
	for (int i = 0; i < BLOCK_LEN; i++)
	{
		for (int j = 0; j < BLOCK_LEN; j++)
		{
			blocks[idx][i][j] = tmp_arr[i][j];
		}
	}
}