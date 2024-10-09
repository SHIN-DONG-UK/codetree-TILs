#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

#define MAX_MAP 29
using namespace std;

struct Point {
	int y;
	int x;
};

struct Group {
	int y;
	int x;
	int cnt;
	int num;
	int group_num;
};

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

int n;
int map[MAX_MAP][MAX_MAP];
int group_id[MAX_MAP][MAX_MAP];
vector<Group> groups;

Point head_point_arr[4];

int ans;

void Input();
int GetScores();
int GetScore(int group1, int group2);
void GetGroups();
void GetGroup(Point sp, int group_num);
void RotateMap();

int main() {
	Input();
	GetGroups();
	//cout << GetScores() << '\n';
	ans += GetScores();
	
	for (int i = 0; i < 3; i++)
	{
		RotateMap();

		memset(group_id, 0, sizeof(group_id));
		groups.clear();
		GetGroups();
		ans += GetScores();
	}
	
	cout << ans << '\n';
	
	return 0;
}

void Input() {
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> map[i][j];
		}
	}
	head_point_arr[0] = { 0,0 };
	head_point_arr[1] = { 0,n / 2 + 1 };
	head_point_arr[2] = { n/2 + 1,0 };
	head_point_arr[3] = { n/2+1,n/2+1 };
}

void GetGroups() {
	int num = 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (group_id[i][j] > 0) continue;
			GetGroup({ i, j }, num);
			num++;
		}
	}
}

void GetGroup(Point sp, int group_num) {
	int cnt = 1;

	queue<Point> q;
	q.push(sp);
	group_id[sp.y][sp.x] = group_num;

	Point cp, np;
	while (!q.empty()) {
		cp = q.front();
		q.pop();

		for (int d = 0; d < 4; d++)
		{
			np = { cp.y + dy[d], cp.x + dx[d] };
			if (np.y < 0 || np.y >= n || np.x < 0 || np.x >= n) continue;
			if (group_id[np.y][np.x] != 0) continue;
			if (map[sp.y][sp.x] != map[np.y][np.x]) continue;

			group_id[np.y][np.x] = group_num;
			q.push(np);

			cnt++;
		}

	}

	Group group = { sp.y, sp.x, cnt, map[sp.y][sp.x], group_num};
	groups.push_back(group);
}

int GetScores() {
	int sum = 0;
	for (int i = 0; i < groups.size() - 1; i++)
	{
		for (int j = i+1; j < groups.size(); j++)
		{
			sum += GetScore(i, j);
		}
	}
	return sum;
}

int GetScore(int group1, int group2) {
	int b = 0;

	Group g1 = groups[group1];
	Group g2 = groups[group2];

	int ny, nx;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (group_id[i][j] == g1.group_num) {
				for (int d = 0; d < 4; d++)
				{
					ny = i + dy[d];
					nx = j + dx[d];
					if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
					if (group_id[ny][nx] == g2.group_num) {
						b++;
					}
				}
			}
		}
	}
	
	return (g1.cnt + g2.cnt) * g1.num * g2.num * b;
}

void RotateMap() {
	int B[MAX_MAP][MAX_MAP] = { 0, };
	// 십자가 모양으로 반시계90도
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			B[i][j] = map[j][n - 1 - i];
		}
	}
	// 나머지 네 영역 시계90도
	for (int k = 0; k < 4; k++)
	{
		for (int i = 0; i < n / 2; i++)
		{
			for (int j = 0; j < n / 2; j++)
			{
				B[head_point_arr[k].y + i][head_point_arr[k].x + j] 
					= map[head_point_arr[k].y + n/2 -1 -j][head_point_arr[k].x + i];
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			map[i][j] = B[i][j];
		}
	}
}