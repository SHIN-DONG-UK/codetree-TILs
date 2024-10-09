#include <iostream>
#include <queue>
#include <cstring>

#define MAX_MAP 5
using namespace std;

struct Point {
	int y;
	int x;
};

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

int k, m;
int map[MAX_MAP][MAX_MAP];
int tmp_map[MAX_MAP][MAX_MAP];
int visited[MAX_MAP][MAX_MAP];
queue<int> wall;

void Input(); // OK
void Simulation();
int FindMaxValueAndRemove(); // OK
int ChainEffect(); // OK

int FindThreeOver(Point sp); // OK
void RemoveParts(Point sp); // OK
void RotateThreeByThree(Point mp, int t); // OK
void CopyMaptoTmp(); // OK
void CopyTmptoMap(); // OK

void AddParts(); // OK

int main() {
	Input();
	Simulation();

	return 0;

}

void Input() {
	cin >> k >> m;
	for (int i = 0; i < MAX_MAP; i++)
	{
		for (int j = 0; j < MAX_MAP; j++)
		{
			cin >> map[i][j];
		}
	}

	int tmp;
	for (int i = 0; i < m; i++)
	{
		cin >> tmp;
		wall.push(tmp);
	}

}

void Simulation() {
	int value;
	for (int i = 0; i < k; i++)
	{
		value = FindMaxValueAndRemove();
		if (value == 0) break;
		AddParts();
		value += ChainEffect();
		if (value != 0) cout << value << ' ';
	}
	cout << '\n';
}

int FindThreeOver(Point sp) {
	int cnt = 0;
	queue<Point> q;
	q.push(sp);
	visited[sp.y][sp.x] = 1;
	cnt++;

	Point cp, np;
	while (!q.empty()) {
		cp = q.front();
		q.pop();

		for (int d = 0; d < 4; d++)
		{
			np = { cp.y + dy[d], cp.x + dx[d] };
			if (np.y < 0 || np.y >= MAX_MAP || np.x < 0 || np.x >= MAX_MAP) continue;
			if (visited[np.y][np.x] == 1) continue;
			if (tmp_map[sp.y][sp.x] != tmp_map[np.y][np.x]) continue;
			
			visited[np.y][np.x] = 1;
			q.push(np);

			cnt++;
		}
	}

	return cnt;
}

void RemoveParts(Point sp) {
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
			if (np.y < 0 || np.y >= MAX_MAP || np.x < 0 || np.x >= MAX_MAP) continue;
			if (visited[np.y][np.x] == 1) continue;
			if (map[sp.y][sp.x] != map[np.y][np.x]) continue;

			visited[np.y][np.x] = 1;
			q.push(np);

			map[np.y][np.x] = -1;
		}
	}
	map[sp.y][sp.x] = -1;
}

void RotateThreeByThree(Point mp, int t) {
	int B[3][3] = { 0, };
	int std_y = mp.y - 1;
	int std_x = mp.x - 1;

	if (t == 0) {
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				B[i][j] = map[2 - j + std_y][i + std_x];
			}
		}
	}
	else if (t == 1) {
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				B[i][j] = map[2 - i + std_y][2 - j + std_x];
			}
		}
	}
	else {
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				B[i][j] = map[j + std_y][2 - i + std_x];
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tmp_map[std_y + i][std_x + j] = B[i][j];
		}
	}
}

void CopyMaptoTmp() {
	for (int i = 0; i < MAX_MAP; i++)
	{
		for (int j = 0; j < MAX_MAP; j++)
		{
			tmp_map[i][j] = map[i][j];
		}
	}
}

void CopyTmptoMap() {
	for (int i = 0; i < MAX_MAP; i++)
	{
		for (int j = 0; j < MAX_MAP; j++)
		{
			map[i][j] = tmp_map[i][j];
		}
	}
}

int FindMaxValueAndRemove() {
	int rst = 0;

	int max_val = 0;
	int max_rot = 0;
	int max_j = -1;
	int max_i = -1;

	for (int rot = 0; rot < 3; rot++)
	{
		for (int j = 1; j < MAX_MAP-1; j++)
		{
			for (int i = 1; i < MAX_MAP-1; i++)
			{
				memset(visited, 0, sizeof(visited));
				int sum = 0;
				int cnt;
				CopyMaptoTmp();
				RotateThreeByThree({ i,j }, rot);
				
				for (int a = 0; a < MAX_MAP; a++)
				{
					for (int b = 0; b < MAX_MAP; b++)
					{
						if (visited[a][b] == 1) continue;
						cnt = FindThreeOver({ a,b });
						if (cnt < 3) continue;
						sum += cnt;
					}
				}
				// 현재 탐사에서 유물수 sum
				if (sum > max_val) {
					max_val = sum;
					max_rot = rot;
					max_j = j;
					max_i = i;
				}
			}
		}
	}

	memset(visited, 0, sizeof(visited));
	CopyMaptoTmp();
	RotateThreeByThree({ max_i,max_j }, max_rot);
	CopyTmptoMap();
	vector<Point> start_points;
	int cnt;
	for (int a = 0; a < MAX_MAP; a++)
	{
		for (int b = 0; b < MAX_MAP; b++)
		{
			if (visited[a][b] == 1) continue;
			cnt = FindThreeOver({ a,b });
			if (cnt >= 3) {
				start_points.push_back({ a,b });
				rst += cnt;
			};
		}
	}
	
	for (int i = 0; i < start_points.size(); i++)
	{
		memset(visited, 0, sizeof(visited));
		RemoveParts(start_points[i]);
	}

	return rst;
}

void AddParts() {
	int part;
	for (int j = 0; j < MAX_MAP; j++)
	{
		for (int i = MAX_MAP - 1; i >= 0; i--)
		{
			if (map[i][j] == -1) {
				part = wall.front();
				wall.pop();
				map[i][j] = part;
			}
		}
	}
	
}

int ChainEffect() {
	int rst = 0;
	int cnt;
	vector<Point> start_points;
	
	while (true) {
		memset(visited, 0, sizeof(visited));
		CopyMaptoTmp();
		start_points.clear();

		for (int a = 0; a < MAX_MAP; a++)
		{
			for (int b = 0; b < MAX_MAP; b++)
			{
				if (visited[a][b] == 1) continue;
				cnt = FindThreeOver({ a,b });
				if (cnt < 3) continue;
				rst += cnt;
				start_points.push_back({ a, b });
			}
		}

		if (start_points.size() == 0) break;
		else {
			for (int i = 0; i < start_points.size(); i++)
			{
				memset(visited, 0, sizeof(visited));
				RemoveParts(start_points[i]);
			}
			AddParts();
		}
	}
	return rst;
}