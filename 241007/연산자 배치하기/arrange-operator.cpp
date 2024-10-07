#include <iostream>
#include <vector>
using namespace std;

int N;
int arr[11];
vector<char> operators;
int visited[10];
int path[10];
int sum;
int min_val = 1e9;
int max_val = -1e9;

void input();
void go(int idx);

int main() {
    input();
    go(0);
    cout << min_val << ' ' << max_val << '\n';
}

void input() {
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }
    int a, b, c;
    cin >> a >> b >> c;
    for (int i = 0; i < a; i++)
        operators.push_back('+');
    for (int i = 0; i < b; i++)
        operators.push_back('-');
    for (int i = 0; i < c; i++)
        operators.push_back('*');
}

void go(int idx) {
    if (idx == N - 1) {
        sum = arr[0];
        for (int i = 0; i < N-1; i++)
        {
            if (operators[path[i]] == '+') {
                sum += arr[i + 1];
            }
            else if (operators[path[i]] == '-') {
                sum -= arr[i + 1];
            }
            else {
                sum *= arr[i + 1];
            }
        }
        if (min_val > sum) min_val = sum;
        if (sum > max_val) max_val = sum;
        return;
    }
    for (int i = 0; i < N - 1; i++) {
        if (visited[i] == 1) continue;
        visited[i] = 1;
        path[idx] = i;
        go(idx + 1);
        visited[i] = 0;
    }
}