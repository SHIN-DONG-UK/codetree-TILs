#include <iostream>
#include <queue>
#include <cstring>

#define MAX_L 40
#define MAX_N 30

#define WALL 2
#define HAM 1
using namespace std;

// 상-우-하-좌
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

struct Knight {
	int x;
	int y;
	int h;
	int w;
	int k;
	int num;
};

int L, N, Q;
int chess_map[MAX_L + 2][MAX_L + 2];
int knight_map[MAX_L + 2][MAX_L + 2];
Knight knight_arr[MAX_N + 1];
int visited[MAX_N + 1];
int damage_arr[MAX_N + 1];
int ans;

void Input();
bool CheckMove(int start_num, int dir);
void MoveKnight(int num, int dir);

void Print();

int main() {
	Input();
	//Print();

	int num, dir;

	for (int i = 0; i < Q; i++)
	{
		cin >> num >> dir;
		if (knight_arr[num].k > 0) {
			if (CheckMove(num, dir)) {
				MoveKnight(num, dir);
				//Print();
			}
		}
	}

	for (int i = 1; i <= N; i++)
	{
		if (knight_arr[i].k > 0)
			ans += damage_arr[i];
	}

	cout << ans << '\n';

	return 0;
}

void Input() {
	cin >> L >> N >> Q;
	// 외벽작업
	for (int i = 0; i < L + 2; i++)
	{
		chess_map[0][i] = WALL;
		chess_map[L + 1][i] = WALL;
		chess_map[i][0] = WALL;
		chess_map[i][L + 1] = WALL;
	}
	for (int i = 1; i <= L; i++)
	{
		for (int j = 1; j <= L; j++)
		{
			cin >> chess_map[i][j];
		}
	}

	int x, y, h, w, k;
	for (int i = 1; i <= N; i++)
	{
		cin >> y >> x >> h >> w >> k;
		knight_arr[i] = { x,y,h,w,k,i };
		// 기사 기록
		for (int a = y; a < y+h; a++)
		{
			for (int b = x; b < x+w; b++)
			{
				knight_map[a][b] = i;
			}
		}
	}

	

}

bool CheckMove(int start_num, int dir) {
	memset(visited, 0, sizeof(visited));

	queue<int> q;
	q.push(start_num);
	visited[start_num] = 1;

	int cur;
	int ny, nx;

	Knight knight;

	while (!q.empty()) {
		cur = q.front();
		q.pop();

		knight = knight_arr[cur];
		
		for (int i = knight.y; i < knight.y+knight.h; i++)
		{
			for (int j = knight.x; j < knight.x+knight.w; j++)
			{
				ny = i + dy[dir];
				nx = j + dx[dir];
				// 1. self -> cut
				if (knight_map[ny][nx] == knight.num)
					continue;
				// 2. wall -> false
				if (chess_map[ny][nx] == WALL)
					return false;
				// 3. blank or hamjung
				// nothing
				// 
				// 4. another knight
				if (knight_map[ny][nx] > 0) {
					if (visited[knight_map[ny][nx]] == 1)
						continue;
					visited[knight_map[ny][nx]] = 1;
					q.push(knight_map[ny][nx]);
				}
			}
		}

	}
	
	return true;
}

void MoveKnight(int num, int dir) {
	memset(knight_map, 0, sizeof(knight_map));
	for (int i = 1; i <= N; i++)
	{
		// 이동하는 기사들은 맵에 반영할지말지 피해보고 판단해야 해서 따로 고려
		if (visited[i] == 1)
		{
			knight_arr[i].y += dy[dir];
			knight_arr[i].x += dx[dir];
			
			int damage = 0;
			
			for (int a = knight_arr[i].y; a < knight_arr[i].y + knight_arr[i].h; a++)
			{
				for (int b = knight_arr[i].x; b < knight_arr[i].x + knight_arr[i].w; b++)
				{
					if (chess_map[a][b] == HAM)
						damage++;
				}
			}

			if (knight_arr[i].num != num) {
				knight_arr[i].k -= damage;
				damage_arr[i] += damage;
			}

			
		}
		// 왜 다르지?
		if (knight_arr[i].k > 0) {
			for (int a = knight_arr[i].y; a < knight_arr[i].y + knight_arr[i].h; a++)
			{
				for (int b = knight_arr[i].x; b < knight_arr[i].x + knight_arr[i].w; b++)
				{
					knight_map[a][b] = knight_arr[i].num;
				}
			}
		}
	}
}

void Print() {
	cout << '\n';
	for (int i = 0; i < L+2; i++)
	{
		for (int j = 0; j < L+2; j++)
		{
			cout << chess_map[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
	cout << '\n';
	for (int i = 0; i < L + 2; i++)
	{
		for (int j = 0; j < L + 2; j++)
		{
			cout << knight_map[i][j] << ' ';
		}
		cout << '\n';
	}
}