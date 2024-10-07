#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

#define MAX_LEN 50
using namespace std;

struct Point {
	int y;
	int x;
};

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

int N;
int L, R;
int map[MAX_LEN][MAX_LEN];
int visited[MAX_LEN][MAX_LEN];
vector<Point> groups[MAX_LEN * MAX_LEN];

int group_len;
int ans;

void Input();
void Solve();
void Init();
void Bfs(Point sp);
void Calc();

void print();

int main() {
	Input();
	Solve();
	
	cout << ans << '\n';
}

void Input() {
	cin >> N >> L >> R;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];
		}
	}
}

void Solve() {
	while (true) {
		Init();

		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++){
				if (visited[i][j] == 1) continue;
				Bfs({ i,j });
				group_len++;
			}
		}

		if (group_len == N * N) break;

		Calc();

		ans++;
	}
}

void Init() {
	memset(visited, 0, sizeof(visited));
	for (int i = 0; i < N * N; i++) {
		if (groups[i].size() == 0) break;
		groups[i].clear();
	}

	group_len = 0;
}

void Bfs(Point sp) {
	queue<Point> q;
	q.push(sp);
	visited[sp.y][sp.x] = 1;
	groups[group_len].push_back(sp);

	Point cp, np;
	while (!q.empty()) {
		cp = q.front();
		q.pop();

		for (int d = 0; d < 4; d++)
		{
			np = { cp.y + dy[d], cp.x + dx[d] };
			if (np.y < 0 || np.y >= N || np.x < 0 || np.x >= N) continue;
			if (visited[np.y][np.x] == 1) continue;
			if (abs(map[cp.y][cp.x] - map[np.y][np.x]) >= L && abs(map[cp.y][cp.x] - map[np.y][np.x]) <= R) {
				visited[np.y][np.x] = 1;
				groups[group_len].push_back(np);
				q.push(np);
			}
		}
	}
}

void Calc() {
	for (int i = 0; i < group_len; i++)
	{
		int val = 0;
		for (int j = 0; j < groups[i].size(); j++)
		{
			val += map[groups[i][j].y][groups[i][j].x];
		}
		val = val / groups[i].size();
		for (int j = 0; j < groups[i].size(); j++)
		{
			map[groups[i][j].y][groups[i][j].x] = val;
		}
	}
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