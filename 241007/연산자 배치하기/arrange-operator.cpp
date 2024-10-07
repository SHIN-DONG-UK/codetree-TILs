#include <iostream>
#include <algorithm>
#define MAX_NUM 11
#define OPERATOR_NUM 3
using namespace std;

int N;
int numbers[MAX_NUM];
// 0 : 덧셈, 1 : 뺄셈, 2 : 곱셈
int operator_cnt[OPERATOR_NUM]; // 얘가 마치 visited처럼 행동
int min_val = 1e9;
int max_val = -1e9;

void input();
void FindMinAndMax(int cnt, int val);
int Calc(int val, int op, int num);

int main() {
	input();
	FindMinAndMax(0, numbers[0]);

	cout << min_val << ' ' << max_val << '\n';
}

void input() {
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> numbers[i];
	for (int i = 0; i < OPERATOR_NUM; i++)
		cin >> operator_cnt[i];
}

void FindMinAndMax(int cnt, int val) {
	if (cnt == N - 1) {
		min_val = min(min_val, val);
		max_val = max(max_val, val);
		return;
	}

	for (int i = 0; i < OPERATOR_NUM; i++)
	{
		if (operator_cnt[i]) {
			operator_cnt[i]--;
			FindMinAndMax(cnt + 1, Calc(val, i, numbers[cnt+1]));
			operator_cnt[i]++;
		}
	}
}

int Calc(int val, int op, int num) {
	if (op == 0) {
		return val + num;
	}
	else if (op == 1) {
		return val - num;
	}
	else {
		return val * num;
	}
}