#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_MAP 100
using namespace std;

struct Point {
	int y;
	int x;
};

// x 우 상 좌 하
int dy[5] = { 0,0,-1,0,1 };
int dx[5] = { 0,1,0,-1,0 };

int n;
int map[MAX_MAP][MAX_MAP];
vector<Point> point_arr;
int ans;

void MakeDragonCurve();
Point RotatePoint(Point std, Point tar);
void Calc();

int main() {
	MakeDragonCurve();
	Calc();

	cout << ans << '\n';
	return 0;
}

void MakeDragonCurve() {
	cin >> n;
	int x, y, d, g;
	for (int i = 0; i < n; i++)
	{
		point_arr.clear();

		cin >> y >> x >> d >> g;
		d++;
		// 0차
		point_arr.push_back({ y, x });
		point_arr.push_back({ y + dy[d], x + dx[d] });
		for (int j = 1; j <= g; j++)
		{
			int idx = point_arr.size() - 1;
			for (int k = idx - 1; k >= 0; k--)
				point_arr.push_back(RotatePoint(point_arr[idx], point_arr[k]));
		}

		// 드래곤 커브 맵에 기록
		for (int i = 0; i < point_arr.size(); i++)
		{
			map[point_arr[i].y][point_arr[i].x] = 1;
		}

	}
}

Point RotatePoint(Point std, Point tar) {
	Point rst = std;

	int y = tar.y - std.y;
	int x = tar.x - std.x;
	int idx = 0;
	if (y < 0) idx = 1;
	else if (y > 0) idx = 3;
	rst.y += dy[idx] * abs(y);
	rst.x += dx[idx] * abs(y);

	idx = 0;
	if (x < 0) idx = 2;
	else if (x > 0) idx = 4;
	rst.y += dy[idx] * abs(x);
	rst.x += dx[idx] * abs(x);

	return rst;
}

void Calc() {
	for (int i = 0; i < MAX_MAP - 1; i++)
	{
		for (int j = 0; j < MAX_MAP - 1; j++)
		{
			if (map[i][j] == 1 && map[i + 1][j] == 1 && map[i][j + 1] == 1 && map[i + 1][j + 1] == 1) ans++;
		}
	}
}