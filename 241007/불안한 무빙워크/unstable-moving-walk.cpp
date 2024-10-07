#include <iostream>

#define MAX_NUM 200
using namespace std;

int N, K;
int moving_walk[MAX_NUM];
int moving_people[MAX_NUM];
int zero_cnt;
int ans;

void input();
void simulation();
void RotateMovingWalk();
void MovePeople();
void AddPeople();
void print();

int main() {
	input();
	simulation();

	cout << ans << '\n';
}

void input() {
	cin >> N >> K;
	for (int i = 0; i < 2*N; i++)
	{
		cin >> moving_walk[i];
	}

} 

void simulation() {
	while (zero_cnt < K) {
		ans++;
		// 1. 무빙워크가 한 칸 회전
		RotateMovingWalk();
		// 2. 사람 이동
		MovePeople();
		// 3. 사람 추가
		AddPeople();
	}
}

void RotateMovingWalk() {
	int tmp = moving_walk[2 * N - 1];
	for (int i = 2 * N - 2; i >= 0; i--)
	{
		moving_walk[i + 1] = moving_walk[i];
	}
	moving_walk[0] = tmp;

	for (int i = N - 2; i >= 0; i--)
	{
		moving_people[i + 1] = moving_people[i];
	}
	moving_people[0] = 0;
	moving_people[N - 1] = 0;

}

void MovePeople() {
	for (int i = N-2; i >= 0; i--)
	{
		if (moving_people[i] == 1) {
			if (moving_walk[i + 1] == 0) continue;
			if (moving_people[i + 1] == 1) continue;
			moving_people[i + 1] = 1;
			moving_people[i] = 0;
			moving_walk[i + 1]--;
			if (moving_walk[i + 1] == 0) zero_cnt++;
		}
	}
	moving_people[N - 1] = 0;
}

void AddPeople() {
	if (moving_walk[0] != 0 && moving_people[0] == 0) {
		moving_people[0] = 1;
		moving_walk[0] += -1;
		if (moving_walk[0] == 0) zero_cnt++;
	}
}
void print() {
	for (int i = 0; i < 10; i++)
	{
		cout << moving_walk[i] << ' ';
	}
	cout << '\n';
}