#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

#define MAX_NUM 11
#define OPERATOR_NUM 3

using namespace std;

int n;
int numbers[MAX_NUM];
int operator_cnt[OPERATOR_NUM]; // 0: 덧셈, 1: 뺄셈, 2: 곱셈
int min_val = INT_MAX, max_val = INT_MIN;

// 모든 연산자가 선택됐을 때 만들어진 식의 값을 반환합니다.
int Calculate(int num1, int num2, int op) {
    // 연산자를 순서대로 적용하여 결과 값을 계산합니다.
    if(op == 0)
        return num1 + num2;
    else if(op == 1)
        return num1 - num2;
    else
        return num1 * num2;
}

void FindMinAndMax(int cnt, int val) {
    // 모든 연산자가 선택됐을 때 만들 수 있는 값으로 정답을 갱신해줍니다.
    if(cnt == n - 1) {
        min_val = min(min_val, val);
        max_val = max(max_val, val);
        return;
    }

    // 사용 가능한 연산자의 후보들을 탐색합니다.
    for(int i = 0; i < OPERATOR_NUM; i++) {
        if(operator_cnt[i]) {
            operator_cnt[i]--;
            FindMinAndMax(cnt + 1, Calculate(val, numbers[cnt + 1], i));
            operator_cnt[i]++;
        }
    }
}

int main() {
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> numbers[i];

    for(int i = 0; i < OPERATOR_NUM; i++)
        cin >> operator_cnt[i]; 

    FindMinAndMax(0, numbers[0]);

    cout << min_val << " " << max_val;
    return 0;
}