#include <iostream>

#define MAX_N 51 // 좌상단 (1, 1)
#define MAX_P 31 // DAT
#define RUDOLP -1
using namespace std;

// 상-우상-우-우하-하-좌하-좌-좌상
// 상우하좌 -> 짝수
// 대각선 -> 홀수
int dy[8] = { -1,-1,0,1,1,1,0,-1 };
int dx[8] = { 0,1,1,1,0,-1,-1,-1 };

struct Point {
	int y;
	int x;
};

struct Santa {
	Point p;
	int num;
	int state; // 0 : 생존
			   // 1 : 기절 -> 산타 to 루돌프
			   // 2 : 기절 -> 루돌프 to 산타
	           // -1 : 탈락
};

int N, M, P, C, D;
int map[MAX_N][MAX_N];
Santa santa_arr[MAX_P];
int santa_pt[MAX_P];
Point rudolp;
int survivor;

void Input();
void Simulation();

void MoveRudolp();
void MoveSantas();
void MoveSanta(Santa* santa);
void ForSurvivor();

int CalcDist(Point* a, Point* b);
void GoAway(int santa_num, int dir, int speed);
void print();

int main() {
	Input();
	Simulation();

	for (int i = 1; i <= P; i++)
		cout << santa_pt[i] << ' ';
	cout << '\n';
	return 0;
}

void Input() {
	cin >> N >> M >> P >> C >> D;
	cin >> rudolp.y >> rudolp.x;
	map[rudolp.y][rudolp.x] = RUDOLP;

	int num, y, x;
	for (int i = 0; i < P; i++)
	{
		cin >> num >> y >> x;
		santa_arr[num] = { y, x, num};
		map[y][x] = num;
	}
	survivor = P;
}

void Simulation() {
	for (int i = 1; i <= M; i++)
	{
		MoveRudolp();
		//print();

		MoveSantas();
		//print();

		// 생존 산타 점수 올려줘
		ForSurvivor();

		if (survivor == 0)
			break;
	}
}

int CalcDist(Point* a, Point* b) {
	return (a->y - b->y) * (a->y - b->y) + (a->x - b->x) * (a->x - b->x);
}

void MoveRudolp() {
	// 1. 가장 가까운 산타
	int min_dist = 1e9;
	int dist;
	Point santa = rudolp;

	for (int i = N; i >= 1; i--)
	{
		for (int j = N; j >= 1; j--)
		{
			if (map[i][j] == 0 || map[i][j] == RUDOLP) continue;
			Point p = { i,j };
			dist = CalcDist(&rudolp, &p);
			if (min_dist > dist) {
				min_dist = dist;
				santa = { i,j };
			}
		}
	}

	min_dist = 1e9;

	int dir = 0;

	Point np;
	// 2. 가장 가까워지는 칸으로 이동
	for (int d = 0; d < 8; d++)
	{
		np = { rudolp.y + dy[d], rudolp.x + dx[d] };
		if (np.y <= 0 || np.y > N || np.x <= 0 || np.x > N) continue;
		if (np.y == santa.y && np.x == santa.x) {
			dir = d;
			break;
		}
		dist = CalcDist(&np, &santa);
		if (min_dist > dist) {
			min_dist = dist;
			dir = d;
		}
	}
	// 찾은 dir으로 루돌프 이동
	// 여기서 루돌프 to 산타 충돌 검사
	map[rudolp.y][rudolp.x] = 0;
	rudolp = { rudolp.y + dy[dir], rudolp.x + dx[dir] };
	if (rudolp.y == santa.y && rudolp.x == santa.x) {
		int num = map[rudolp.y][rudolp.x];
		santa_pt[num] += C;
		santa_arr[num].state = 2; // 산타 기절
		GoAway(num, dir, C);
	}
	map[rudolp.y][rudolp.x] = RUDOLP;

}

void MoveSantas() {
	for (int i = 1; i <= P; i++)
	{
		if (santa_arr[i].state > 0) {
			santa_arr[i].state--;
			continue;
		}
		if (santa_arr[i].state == -1)
			continue;
		MoveSanta(santa_arr + i);
	}
}

void MoveSanta(Santa* santa) {
	Point np = { santa->p.y, santa->p.x };
	int dist;
	int min_dist = CalcDist(&np, &rudolp); // ****** 실수 고 위험 부위
	int dir = -1;
	// 상-우-하-좌
	for (int d = 0; d < 8; d+=2)
	{
		np = { santa->p.y + dy[d], santa->p.x + dx[d] };
		if (np.y <= 0 || np.y > N || np.x <= 0 || np.x > N) continue;
		if (map[np.y][np.x] > 0) continue; // 루돌프를 컷하면 안됨(루돌프 == 음수)
		dist = CalcDist(&np, &rudolp);
		if (min_dist > dist) {
			min_dist = dist;
			dir = d;
		}
	}
	// dir이 -1이면 이동할 수 없음
	if (dir != -1) {
		// 여기서 산타 to 루돌프 충돌 검사를 해야 함
		map[santa->p.y][santa->p.x] = 0;
		santa->p.y = santa->p.y + dy[dir];
		santa->p.x = santa->p.x + dx[dir];
		if (santa->p.y == rudolp.y && santa->p.x == rudolp.x) {
			santa_pt[santa->num] += D;
			santa->state = 1; // 산타 기절
			GoAway(santa->num, (dir + 4) % 8, D);
		}
		else
			map[santa->p.y][santa->p.x] = santa->num;
	}
}

void GoAway(int santa_num, int dir, int speed) {
	int flag = false;
	// 초기 충돌
	Point np = { santa_arr[santa_num].p.y + dy[dir] * speed, santa_arr[santa_num].p.x + dx[dir] * speed };
	// 맵 밖으로 나간 경우
	if (np.y <= 0 || np.y > N || np.x <= 0 || np.x > N) {
		santa_arr[santa_num].state = -1; // 맵에는 기록 안해도 되고 상태 업데이트
		survivor--;
	}
		
	else if (map[np.y][np.x] == 0) {
		// 맵 업데이트
		map[np.y][np.x] = santa_num;
		// 배열 업데이트
		santa_arr[santa_num].p.y = np.y;
		santa_arr[santa_num].p.x = np.x;
	}
	else {
		// 연쇄 충돌
		int cur = map[np.y][np.x];
		int prev;
		// 맵 업데이트
		map[np.y][np.x] = santa_num;
		// 배열 업데이트
		santa_arr[santa_num].p.y = np.y;
		santa_arr[santa_num].p.x = np.x;

		// 연쇄 충돌 시작
		while (true) {
			np = { santa_arr[cur].p.y + dy[dir], santa_arr[cur].p.x + dx[dir] };
			if (np.y <= 0 || np.y > N || np.x <= 0 || np.x > N) {
				santa_arr[cur].state = -1;
				survivor--;
				break;
			}
			else if (map[np.y][np.x] == 0) {
				// 맵 업데이트
				map[np.y][np.x] = cur;
				// 배열 업데이트
				santa_arr[cur].p.y = np.y;
				santa_arr[cur].p.x = np.x;
				// 종료
				break;
			}
			else {
				prev = cur;
				cur = map[np.y][np.x];
				// 맵 업데이트
				map[np.y][np.x] = prev;
				// 배열 업데이트
				santa_arr[prev].p.y = np.y;
				santa_arr[prev].p.x = np.x;
			}
		}
	}
}


void print() {
	cout << '\n';
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cout << map[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
}

void ForSurvivor() {
	for (int i = 1; i <= P; i++)
	{
		if (santa_arr[i].state == -1)
			continue;
		santa_pt[i]++;
	}
}