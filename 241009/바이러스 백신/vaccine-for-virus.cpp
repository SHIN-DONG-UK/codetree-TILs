#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

#define MAX_MAP 50
#define MAX_VIRUS 10
using namespace std;

struct Point {
	int y;
	int x;
};
// 상하좌우
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

int n, m;
int map[MAX_MAP][MAX_MAP];
int visited[MAX_MAP][MAX_MAP];
vector<Point> hospitals;
int path[MAX_VIRUS];
int ans = 1e9;

void Input();
int RemoveVirus(int* arr, int len);
void GetCombinationAndRun(int idx, int start);
bool CheckVirus();

int main() {
	Input();
	GetCombinationAndRun(0, 0);

	if (ans == 1e9) cout << "-1\n";
	else if (ans == 0) cout << "0\n";
	else cout << ans - 1 << '\n';
	return 0;
}

void Input() {
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == 2) hospitals.push_back({ i, j });
		}
	}
}

int RemoveVirus(int* arr, int len) {
	memset(visited, 0, sizeof(visited));
	int rst = 0;

	queue<Point> q;
	for (int i = 0; i < len; i++) {
		q.push(hospitals[arr[i]]);
		visited[hospitals[arr[i]].y][hospitals[arr[i]].x] = 1;
	}
	
	Point cp, np;
	while (!q.empty()) {
		cp = q.front();
		q.pop();

		for (int d = 0; d < 4; d++)
		{
			np = { cp.y + dy[d], cp.x + dx[d] };
			if (np.y < 0 || np.y >= n || np.x < 0 || np.x >= n) continue;
			if (visited[np.y][np.x] > 0) continue;
			if (map[np.y][np.x] == 1) continue;
			visited[np.y][np.x] = visited[cp.y][cp.x] + 1;
			q.push(np);

			// 정답 제출용
			if (map[np.y][np.x] != 2 && visited[np.y][np.x] > rst) rst = visited[np.y][np.x];
		}
	}
	if (!CheckVirus()) return -1;
	return rst;
}

void GetCombinationAndRun(int idx, int start) {
	if (idx == m) {
		int tmp = RemoveVirus(path, m);
		if (tmp != -1 && ans > tmp) ans = tmp;
		return;
	}

	for (int i = start; i < hospitals.size(); i++)
	{
		path[idx] = i;
		GetCombinationAndRun(idx + 1, i + 1);
	}
}

bool CheckVirus() {
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (map[i][j] == 0 && visited[i][j] == 0) return false;
		}
	}
	return true;
}