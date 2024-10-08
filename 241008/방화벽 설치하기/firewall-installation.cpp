#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

#define MAX_LEN 8
using namespace std;

struct Point {
	int y;
	int x;
};

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

int n, m;
int map[MAX_LEN][MAX_LEN];
int map_copy[MAX_LEN][MAX_LEN];
int visited[MAX_LEN][MAX_LEN];
int path[3];
vector<Point> fires;
vector<Point> blanks;
int ans;

void Input();
void FireSpread(Point sp);
void GetCombinationAndUpdate(int cnt, int start);
int CalcBlanks();
void InitCopy();

int main() {
	Input();
	GetCombinationAndUpdate(0, 0);

	cout << ans << '\n';
	return 0;
}

void Input() {
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == 2) fires.push_back({ i,j });
			else if (map[i][j] == 0) blanks.push_back({ i,j });
		}
	}
}

void FireSpread(Point sp) {
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
			if (np.y < 0 || np.y >= n || np.x < 0 || np.x >= m) continue;
			if (visited[np.y][np.x] == 1) continue;
			if (map_copy[np.y][np.x] == 0) {
				visited[np.y][np.x] = 1;
				map_copy[np.y][np.x] = 2;
				q.push(np);
			}
		}

	}
}

void GetCombinationAndUpdate(int cnt, int start) {
	if (cnt == 3) {
		memset(visited, 0, sizeof(visited));
		InitCopy();

		int y, x;
		for (int i = 0; i < 3; i++)
		{
			y = blanks[path[i]].y;
			x = blanks[path[i]].x;
			map_copy[y][x] = 1;
		}

		for (int i = 0; i < fires.size(); i++) 
			FireSpread(fires[i]);
			
		int blank_cnt = CalcBlanks();
		if (blank_cnt > ans) ans = blank_cnt;

		return;
	}

	for (int i = start; i < blanks.size(); i++)
	{
		path[cnt] = i;
		GetCombinationAndUpdate(cnt + 1, i + 1);
	}
}

void InitCopy() {
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			map_copy[i][j] = map[i][j];
		}
	}
}

int CalcBlanks() {
	int rst = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (map_copy[i][j] == 0) rst++;
		}
	}
	return rst;
}