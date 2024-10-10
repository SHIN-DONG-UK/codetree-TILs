#include <iostream>

#define MAX_MAP 499
#define MAX_DUST 10
using namespace std;

struct Point {
	int y;
	int x;
};

struct Info {
	int dy;
	int dx;
	int per;
};

// mapping
Info mapping[4][MAX_DUST] = {
	{{-2,0,2},{-1,-1,10},{-1,0,7},{-1,1,1},{0,-2,5}, {1,-1,10},{1,0,7},{1,1,1},{2,0,2},{0,-1,-1}},
	{{-1,-1,1},{-1,1,1},{0,-2,2},{0,-1,7},{0,1,7},{0,2,2},{1,-1,10},{1,1,10},{2,0,5},{1,0,-1}},
	{{-2,0,2},{-1,-1,1},{-1,0,7},{-1,1,10},{0,2,5},{1,-1,1},{1,0,7},{1,1,10},{2,0,2},{0,1,-1}},
	{{-2,0,5},{-1,-1,10},{-1,1,10},{0,-2,2},{0,-1,7},{0,1,7},{0,2,2},{1,-1,1},{1,1,1},{-1,0,-1}},
};

// 왼-아래-오-위
int dy[4] = { 0,1,0,-1 };
int dx[4] = { -1,0,1,0 };

int n;
int map[MAX_MAP][MAX_MAP];
int map_debug[MAX_MAP][MAX_MAP];
int ans;

void Input();
void GoRound();
int CalcDust(Point cp, int dir);

int main() {
	
	Input();
	GoRound();

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
}


void GoRound() {
	Point cp = { n / 2, n / 2 };
	Point np;
	int dir = 0;

	int len_updown = 1;
	int len_leftright = 1;

	bool flag = true;
	while (flag) {
		if (dir % 2 == 0) {
			for (int a = 0; a < len_leftright; a++)
			{
				np = { cp.y + dy[dir], cp.x + dx[dir] };

				ans += CalcDust(np, dir);

				if (np.y == 0 && np.x == 0) {
					flag = false;
					break;
				}
				cp = np;
			}
			len_leftright++;
		}
		else {
			for (int a = 0; a < len_updown; a++)
			{
				np = { cp.y + dy[dir], cp.x + dx[dir] };

				ans += CalcDust(np, dir);

				cp = np;
			}
			len_updown++;
		}

		dir = (dir + 1 + 4) % 4;
	}
}

int CalcDust(Point sp, int dir) {
	int rst = 0; // 밖으로 나간 양
	int sub = 0; // 이동 양

	if (map[sp.y][sp.x] == 0) return rst;

	int dust;
	Point np;

	for (int i = 0; i < MAX_DUST - 1; i++)
	{

		np = { sp.y + mapping[dir][i].dy, sp.x + mapping[dir][i].dx };

		dust = map[sp.y][sp.x] * mapping[dir][i].per / 100;

		if (np.y < 0 || np.y >= n || np.x < 0 || np.x >= n)
			rst += dust;
		else 
			map[np.y][np.x] += dust;
		sub += dust;
		
			

		
	}
	np = { sp.y + mapping[dir][MAX_DUST - 1].dy, sp.x + mapping[dir][MAX_DUST - 1].dx };
	if (np.y < 0 || np.y >= n || np.x < 0 || np.x >= n) {
		rst += (map[sp.y][sp.x] - sub);
	}
	else
		map[np.y][np.x] += (map[sp.y][sp.x] - sub);

	map[sp.y][sp.x] = 0;

	return rst;
}