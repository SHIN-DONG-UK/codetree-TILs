#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

#define MAX_N 71 // 좌상단을 (1, 1)로 정의
#define EXIT 9999
#define RIGHT 1
#define DOWN 2
#define LEFT 3
using namespace std;

struct Soul {
	int y;
	int x;
	int now_golem;
};

struct Golem {
	int y;
	int x;
	int exit_dir;
};
// 상우하좌
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

int R, C, K;
int map[MAX_N][MAX_N];
int visited[MAX_N][MAX_N];
vector<Golem> golems;
int ans;

void Input();
void Simulation();

Golem MoveGolem(Golem golem, int num);
void MoveSoul(Golem golem);
bool CheckThree(Golem golem, int dir);
int CalcSoul();

void print();
void print_visited();

int main() {
	Input();
	Simulation();

	cout << ans << '\n';

	return 0;
}

void Input() {
	cin >> R >> C >> K;
	int c, d;
	for (int i = 0; i < K; i++)
	{
		cin >> c >> d;
		golems.push_back({ 0, c, d });
	}
}

void Simulation() {
	int num = 1;
	for (int i = 0; i < golems.size(); i++)
	{
		Golem golem = MoveGolem(golems[i], num);

		//print();

		if (golem.y != -1) {
			memset(visited, 0, sizeof(visited));

			MoveSoul(golem);

			//print_visited();

			ans += CalcSoul();

			num++;
		}
		else
			num = 1;
	}
}

void MoveSoul(Golem golem) {
	Soul soul = { golem.y, golem.x, map[golem.y][golem.x] };
	queue<Soul> q;
	q.push(soul);
	visited[soul.y][soul.x] = 1;

	Soul cur, next;
	while (!q.empty()) {
		cur = q.front();
		q.pop();

		for (int d = 0; d < 4; d++)
		{
			next = { cur.y + dy[d], cur.x + dx[d], cur.now_golem};
			if (next.y <= 0 || next.y > R || next.x <= 0 || next.x > C) continue;
			if (visited[next.y][next.x] > 0) continue;
			if (map[next.y][next.x] == 0) continue;
			if (map[next.y][next.x] != cur.now_golem) {
				// 내 출구다
				if (map[next.y][next.x] == EXIT - cur.now_golem) {
					// 간다
					visited[next.y][next.x] = visited[cur.y][cur.x] + 1;
					q.push(next);
				}
				// 넘의 출구다
				else if (map[next.y][next.x] > 1000) {
					// 현재가 내출구면 간다
					if (map[cur.y][cur.x] == EXIT - cur.now_golem) {
						visited[next.y][next.x] = visited[cur.y][cur.x] + 1;
						next.now_golem = 9999 - map[next.y][next.x];
						q.push(next);
					}
					// 아님 못간다
				}
				// 그냥 다른 골렘이다
				else {
					// 현재가 내 출구면 간다
					if (map[cur.y][cur.x] == EXIT - cur.now_golem) {
						visited[next.y][next.x] = visited[cur.y][cur.x] + 1;
						next.now_golem = map[next.y][next.x];
						q.push(next);
					}
				}
			}
			else {
				visited[next.y][next.x] = visited[cur.y][cur.x] + 1;
				q.push(next);
			}
		}
	}

}
Golem MoveGolem(Golem golem, int num) {
	// 갈 수 있으면 일단 가야함
	// 골렘이 더 이상 움직일 수 없을때 맵에 기록하자
	int flag = false;
	Golem cur = golem;
	Golem next;

	while (true)
	{
		flag = false;
		// 우선순위 1 : 남쪽
		next = { cur.y + dy[DOWN], cur.x + dx[DOWN], cur.exit_dir };
		if (CheckThree(next, DOWN)) {
			cur = next;
			flag = true;
		}
		if (!flag) {
			// 우선순위 2 : 서쪽으로 회전하며 내려가기
			// step1. 왼쪽 검사
			next = { cur.y + dy[LEFT], cur.x + dx[LEFT], cur.exit_dir };
			if (CheckThree(next, LEFT)) {
				// step2. 아래쪽 검사
				next = { next.y + dy[DOWN], next.x + dx[DOWN], next.exit_dir };
				if (CheckThree(next, DOWN)) {
					cur = next;
					// 출구 방향 조정
					cur.exit_dir = (next.exit_dir - 1 + 4) % 4;
					flag = true;
				}
			}
		}
		if (!flag) {
			// 우선순위 3 : 동쪽으로 회전하며 내려가기
			// step1. 오른쪽 검사
			next = { cur.y + dy[RIGHT], cur.x + dx[RIGHT], cur.exit_dir };
			if (CheckThree(next, RIGHT)) {
				// step2. 아래쪽 검사
				next = { next.y + dy[DOWN], next.x + dx[DOWN], next.exit_dir };
				if (CheckThree(next, DOWN)) {
					cur = next;
					// 출구 방향 조정
					cur.exit_dir = (next.exit_dir + 1) % 4;
					flag = true;
				}
			}
		}
		// 반복을 계속할까 말까
		// 어떻게 정해? -> flag세워
		if (!flag) break;
	}
	// 이제 현재 골렘의 위치를 검사해준다
	// 골렘의 위치가 0이다? 맵 초기화
	// **************여기서 실수 -> 골렘을 다 검사해줘야함 **********************
	// ㄱㅊ? -> 맵에 기록
	// 각 골렘을 구분해줘야 한다
	// 출구도 구분해줘야 할까?
	// 출구는 구분 안해도 된다
	int ny, nx;
	for (int d = 0; d < 4; d++)
	{
		ny = cur.y + dy[d];
		nx = cur.x + dx[d];
		if (ny <= 0 || ny > R || nx <= 0 || nx > C) {
			memset(map, 0, sizeof(map));
			cur = { -1,-1,-1 };
			break;
		}
	}

	if(cur.y != -1){
		int ny, nx;
		map[cur.y][cur.x] = num;
		for (int d = 0; d < 4; d++)
		{
			ny = cur.y + dy[d];
			nx = cur.x + dx[d];
			if (d == cur.exit_dir)
				map[ny][nx] = EXIT - num;
			else
				map[ny][nx] = num;
		}
	}
	return cur;
}

bool CheckThree(Golem golem, int dir) {
	Golem next;

	for (int d = 0; d < 4; d++)
	{
		next = { golem.y + dy[d], golem.x + dx[d], golem.exit_dir };
		if ((dir + 2) % 4 == d) continue;
		if (next.y > R || next.x <= 0 || next.x > C) return false;
		if (map[next.y][next.x] != 0) return false;
	}

	return true;
}

void print() {
	cout << '\n';
	for (int i = 1; i <= R; i++)
	{
		for (int j = 1; j <= C; j++)
		{
			if (map[i][j] > 1000) cout << "c ";
			else cout << map[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
}

void print_visited() {
	cout << '\n';
	for (int i = 1; i <= R; i++)
	{
		for (int j = 1; j <= C; j++)
		{
			cout << visited[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
}

int CalcSoul() {
	for (int i = R; i >= 1; i--) {
		for (int j = 1; j <= C; j++)
		{
			if (visited[i][j] > 0)
			{
				return i;
			}
		}
	}
	return 0;
}