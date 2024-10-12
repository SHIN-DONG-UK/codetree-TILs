#include <iostream>
#include <queue>
#include <cstring>
#include <vector>

#define MAX_MAP 5
using namespace std;

struct Point {
	int y;
	int x;
};

// 상하좌우
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
int K, M;
int map[MAX_MAP][MAX_MAP];
int next_map[MAX_MAP][MAX_MAP];
int visited[MAX_MAP][MAX_MAP];

queue<int> wall_num;
vector<Point> start_points; // 3개 이상 연결된 조각의 위치

void Input();
bool FindMax(); // OK -> 회전을 정하는 함수
void CopyMapToNext(); // OK
void CopyNextToMap(); // OK
void RotateMap(int mid_y, int mid_x, int rot); // OK
int GetVal(); // return : 맵 전체 돌면서 조각 수 합
int Bfs(Point sp, int flag); // return : sp에서 조각 수
int RemoveAndAdd(); // return : 현재 턴에서 제거되는 조각 수

void Print();

int main() {
	Input();
	
	for (int i = 0; i < K; i++)
	{
		if (FindMax()) {
			int now_pt = RemoveAndAdd();
			cout << now_pt << ' ';
			//Print();
		}
		else
			break;
	}
	return 0; 
}

void Input() {
	cin >> K >> M;
	for (int i = 0; i < MAX_MAP; i++)
	{
		for (int j = 0; j < MAX_MAP; j++)
		{
			cin >> map[i][j];
		}
	}
	int num;
	for (int i = 0; i < M; i++)
	{
		cin >> num;
		wall_num.push(num);
	}
}

bool FindMax() {
	int max_val = -1; // max_val이 0일 수도 있음
	int max_rot, max_j, max_i;

	int val;
	for (int rot = 0; rot < 3; rot++)
	{
		// 중심 좌표 기준
		for (int j = 1; j <= 3; j++)
		{
			for (int i = 1; i <= 3; i++)
			{
				RotateMap(i, j, rot);
				//Print();
				val = GetVal();
				if (val > max_val) {
					max_val = val;
					max_rot = rot;
					max_j = j;
					max_i = i;
				}
			}
		}
	}
	
	//cout << "max_rot : " << max_rot << '\n';
	//cout << "max_j : " << max_j << '\n';
	//cout << "max_i : " << max_i << '\n';
	
	// Max Point와 rot을 찾음
	// 원래 맵에 적용
	if (max_val != 0) {
		RotateMap(max_i, max_j, max_rot);
		CopyNextToMap();
		return true;
	}
	return false;
}

int RemoveAndAdd() {
	// rst => 현재 턴에서 제거되는 유물 수
	int rst = 0;
	while (true) {
		// start_points 획득
		memset(visited, 0, sizeof(visited));
		vector<Point> start_points;
		int cnt;
		for (int i = 0; i < MAX_MAP; i++)
		{
			for (int j = 0; j < MAX_MAP; j++)
			{
				if (visited[i][j] == 1)
					continue;
				cnt = Bfs({ i,j }, 1);
				if (cnt >= 3) {
					start_points.push_back({ i, j });
					rst += cnt;
				}
					
			}
		}

		if (start_points.size() == 0)
			return rst;

		// 제거
		memset(visited, 0, sizeof(visited));

		for (int i = 0; i < start_points.size(); i++)
		{
			Bfs(start_points[i], 2);
		}

		// 채워 넣어
		int num;
		for (int j = 0; j < MAX_MAP; j++)
		{
			for (int i = MAX_MAP - 1; i >= 0; i--)
			{
				if (map[i][j] == 0) {
					num = wall_num.front();
					wall_num.pop();
					map[i][j] = num;
				}
			}
		}

		//Print();
		
	}
	return rst;
}

void RotateMap(int mid_y, int mid_x, int rot) {
	CopyMapToNext();
	// 90도
	if (rot == 0) {
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				next_map[mid_y - 1 + i][mid_x - 1 + j] = map[mid_y + 1 - j][mid_x - 1 + i];
			}
		}
	}
	// 180도
	else if (rot == 1) {
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				next_map[mid_y - 1 + i][mid_x - 1 + j] = map[mid_y + 1 - i][mid_x + 1 - j];
			}
		}

	}
	//270 도
	else {
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				next_map[mid_y - 1 + i][mid_x - 1 + j] = map[mid_y - 1 + j][mid_x + 1 - i];
			}
		}
	}
}

void CopyMapToNext() {
	for (int i = 0; i < MAX_MAP; i++)
	{
		for (int j = 0; j < MAX_MAP; j++)
		{
			next_map[i][j] = map[i][j];
		}
	}
}

void CopyNextToMap() {
	for (int i = 0; i < MAX_MAP; i++)
	{
		for (int j = 0; j < MAX_MAP; j++)
		{
			map[i][j] = next_map[i][j];
		}
	}
}

// 5x5모두 시작하면서 3개 이상인 애들 찾고 합 리턴하는 함수
int GetVal() {
	memset(visited, 0, sizeof(visited));

	int rst = 0;
	int cnt = 0;
	for (int i = 0; i < MAX_MAP; i++)
	{
		for (int j = 0; j < MAX_MAP; j++)
		{
			if (visited[i][j] == 1)
				continue;
			cnt = Bfs({ i, j }, 0);
			if (cnt >= 3)
				rst += cnt;
		}
	}

	return rst;
}

int Bfs(Point sp, int flag) {
	queue<Point> q;
	q.push(sp);
	visited[sp.y][sp.x] = 1;
	
	int cnt = 1;

	Point cp, np;
	while (!q.empty()) {
		cp = q.front();
		q.pop();

		for (int d = 0; d < 4; d++)
		{
			np = { cp.y + dy[d], cp.x + dx[d] };
			if (np.y < 0 || np.y >= MAX_MAP || np.x < 0 || np.x >= MAX_MAP)
				continue;
			if (visited[np.y][np.x] == 1)
				continue;
			if (flag == 0) { // 0이면 next map 검사
				if (next_map[np.y][np.x] != next_map[sp.y][sp.x])
					continue;
			}
			else {// 1또는 2이면 map 검사
				if (map[np.y][np.x] != map[sp.y][sp.x])
					continue;
			}
			// 2면 map에서 제거

			visited[np.y][np.x] = 1;
			q.push(np);

			if (flag == 2)
				map[np.y][np.x] = 0;

			cnt += 1;
		}
	}

	if(flag == 2)
		map[sp.y][sp.x] = 0;

	return cnt;
}

void Print() {
	cout << '\n';
	for (int i = 0; i < MAX_MAP; i++)
	{
		for (int j = 0; j < MAX_MAP; j++)
		{
			cout << map[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
	cout << '\n';
	for (int i = 0; i < MAX_MAP; i++)
	{
		for (int j = 0; j < MAX_MAP; j++)
		{
			cout << next_map[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
}