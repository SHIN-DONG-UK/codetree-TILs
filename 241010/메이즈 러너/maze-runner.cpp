#include <iostream>
#include <algorithm>
#include <queue>

#define MAX_N 10

using namespace std;

struct Point {
	int y;
	int x;
};

// 상하 좌우
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

int N, M, K;
int map[MAX_N][MAX_N];
queue<Point> participants;
Point exit_point;

int ans;

void Input();
void Simulation();
void MoveParticipants();
void RotateMaze();
void print();

int main() {
	Input();
	Simulation();

	cout << ans << '\n';
	cout << exit_point.y + 1 << ' ' << exit_point.x + 1<< '\n';
	return 0;
}

void Input() {
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];
		}
	}
	int y, x;
	for (int i = 0; i < M; i++)
	{
		cin >> y >> x;
		participants.push({ y - 1, x - 1 });
	}

	cin >> y >> x;
	exit_point = { y - 1, x - 1 };
}

void Simulation() {
	for (int i = 0; i < K; i++)
	{
		MoveParticipants();
		if (participants.size() == 0) return;
		RotateMaze();

	}
}
void MoveParticipants() {
	Point cp, np;
	int dist_cp_to_exit = 0;
	int dist_np_to_exit = 0;
	
	int len = participants.size();
	for (int i = 0; i < len; i++)
	{
		bool flag = true;
		cp = participants.front();
		participants.pop();
		dist_cp_to_exit = abs(cp.y - exit_point.y) + abs(cp.x - exit_point.x);

		for (int d = 0; d < 4; d++)
		{
			np = { cp.y + dy[d], cp.x + dx[d] };
			dist_np_to_exit = abs(np.y - exit_point.y) + abs(np.x - exit_point.x);
			if (np.y < 0 || np.y >= N || np.x < 0 || np.x >= N) continue;
			if (map[np.y][np.x] > 0) continue;
			if (dist_np_to_exit >= dist_cp_to_exit) continue;
			if (np.y == exit_point.y && np.x == exit_point.x) {
				flag = false;
				ans += 1;
				break;
			}

			// 정답 누적
			ans += 1;

			participants.push(np);
			flag = false;
			break;
		}
		// 만약 아무데도 못가면 다시 큐에 넣어줘야 함
		if (flag) participants.push(cp); 
	}
}

void RotateMaze() {
	Point parti;
	int len = participants.size();
	for (int i = 0; i < len; i++)
	{
		parti = participants.front();
		participants.pop();
		map[parti.y][parti.x] += 100;
	}
	map[exit_point.y][exit_point.x] = 9999;

	//print();

	int tar_y = 0;
	int tar_x = 0;
	int tar_l = 2;
	int flag = false;

	// 가장 작은 정사각형 찾기
	for (int l = 2; l <= N; l++)
	{
		if (flag)
			break;
		for (int i = 0; i <= N - l; i++)
		{
			if (flag)
				break;
			for (int j = 0; j <= N - l; j++)
			{
				bool flag_parti = false;
				bool flag_exit = false;
				for (int a = 0; a < l; a++)
				{
					for (int b = 0; b < l; b++)
					{
						if (map[i + a][j + b] > 10 && map[i + a][j + b] < 9999)
							flag_parti = true;
						if (map[i + a][j + b] == 9999)
							flag_exit = true;
					}
				}
				if (flag_parti && flag_exit) {
					tar_l = l; tar_y = i; tar_x = j;
					flag = true;
					break;
				}
			}
		}
	}

	int B[MAX_N][MAX_N] = { 0, };
	for (int i = 0; i < tar_l; i++)
	{
		for (int j = 0; j < tar_l; j++)
		{
			B[tar_y + i][tar_x + j] = map[tar_y + tar_l - 1 - j][tar_x + i];
		}
	}
	for (int i = 0; i < tar_l; i++)
	{
		for (int j = 0; j < tar_l; j++)
		{
			if (B[tar_y + i][tar_x + j] > 0 && B[tar_y + i][tar_x + j] < 10)
				map[tar_y + i][tar_x + j] = B[tar_y + i][tar_x + j] - 1;
			else
				map[tar_y + i][tar_x + j] = B[tar_y + i][tar_x + j];
		}
	}
	//print();
	// 표시했던 출구랑 맵 획득
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (map[i][j] == 9999) {
				exit_point = { i, j };
				map[i][j] = 0;
			}
				
			else if (map[i][j] > 10)
			{
				int len = map[i][j] / 100;
				map[i][j] = 0;
				for (int k = 0; k < len; k++)
					participants.push({ i, j });
			}
		}
	}
	//print();
}

void print() {
	cout << '\n';
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << map[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
}