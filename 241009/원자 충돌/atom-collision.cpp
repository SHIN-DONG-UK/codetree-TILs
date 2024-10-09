#include <iostream>
#include <vector>

#define MAX_MAP 50
using namespace std;

struct Point {
	int y;
	int x;
};

struct Atom {
	int m;
	int s;
	int d;
};

int dy[8] = { -1,-1,0,1,1,1,0,-1 };
int dx[8] = { 0,1,1,1,0,-1,-1,-1 };

vector<Atom> map[MAX_MAP][MAX_MAP];
vector<Atom> map_tmp[MAX_MAP][MAX_MAP];
int N, M, K;

void Input();
void Simulation();

void MoveAtoms();
void MoveAtom(Point p); // -> map_tmp에 반영 // OK
bool AddAtoms(); // -> map에 반영
int CalcMass();
void CopyTmpToMap();

int main() {
	Input();
	Simulation();

	return 0;
}

void Input() {
	cin >> N >> M >> K;
	
	int x, y, m, s, d;
	for (int i = 0; i < M; i++)
	{
		cin >> y >> x >> m >> s >> d;
		map[y - 1][x - 1].push_back({ m,s,d });
	}
}

void Simulation() {
	for (int i = 0; i < K; i++)
	{
		MoveAtoms();
		if(!AddAtoms())
			CopyTmpToMap();
	}
	cout << CalcMass() << '\n';
}



void MoveAtoms() {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (map[i][j].size() > 0) {
				MoveAtom({ i,j });
			}
		}
	}
}

void MoveAtom(Point p) {
	Point np;
	Atom atom;

	// map에 있던 atom 다 빼고, map_tmp에 일단 다 집어넣어
	int len = map[p.y][p.x].size();
	for (int i = len-1; i >= 0; i--)
	{
		atom = map[p.y][p.x].back();
		map[p.y][p.x].pop_back();
		np = { (p.y + dy[atom.d] * atom.s + N) % N, (p.x + dx[atom.d] * atom.s + N) % N};
		map_tmp[np.y][np.x].push_back(atom);
	}

}

bool AddAtoms() {
	bool rst = false;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (map_tmp[i][j].size() <= 1) continue;
			rst = true;
			bool flag = true;

			Atom atom = map_tmp[i][j].back();
			map_tmp[i][j].pop_back();

			int tar_m = atom.m;
			int tar_s = atom.s;
			int std_d = atom.d;

			int len = map_tmp[i][j].size();

			for (int k = len- 1; k >= 0; k--)
			{
				atom = map_tmp[i][j].back();
				map_tmp[i][j].pop_back();

				if (atom.d % 2 != std_d % 2)
					flag = false;

				tar_m += atom.m;
				tar_s += atom.s;
			}

			tar_m /= 5;
			if (tar_m == 0) continue; // 해당 합성은 종료되었음.
			tar_s /= len + 1;

			if (flag) {
				// 상하좌우
				for (int d = 0; d < 8; d+=2)
					map[i][j].push_back({ tar_m, tar_s, d });
			}
			else {
				// 대각선
				for (int d = 0; d < 8; d += 2)
					map[i][j].push_back({ tar_m, tar_s, d });
			}
		}
	}

	return rst;
}

int CalcMass() {
	int rst = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (map[i][j].size() > 0) {
				for (int k = 0; k < map[i][j].size(); k++)
				{
					rst += map[i][j][k].m;
				}
			}
		}
	}
	return rst;
}

void CopyTmpToMap() {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			map[i][j] = map_tmp[i][j];
		}
	}
}