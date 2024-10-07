#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
int P[20][20];
vector<int> v1;
vector<int> v2;
int visited[20];

void input();
void go(int idx, int);
int calc1();
int calc2();
int ans = 1e9;

int main() {
  input();
  go(0, 0);

  cout << ans << '\n';
}

void input() {
  cin >> N;
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      cin >> P[i][j];
    }
  }
}

void go(int idx, int start) {
  if (idx == N/2) {
    for (int i = 0; i < N; i++){
      if (visited[i] == 1) continue;
      v2.push_back(i);
    }
    int sum1 = calc1();
    int sum2 = calc2();
    if (ans > abs(sum1 - sum2)) ans = abs(sum1 - sum2);
    v2.clear();
    return;
  }

  for (int i = start; i < N; i++)
  {
    if (visited[i] == 1) continue;
    visited[i] = 1;
    v1.push_back(i);
    go(idx + 1, i + 1);
    visited[i] = 0;
    v1.pop_back();
  }

}

int calc1() {
  int rst = 0;

  for (int i = 0; i < N/2; i++)
  {
    for (int j = 0; j < N/2; j++)
    {
      if (i == j) continue;
      rst += P[v1[i]][v1[j]];
    }
  }

  return rst;
}

int calc2() {
  int rst = 0;

  for (int i = 0; i < N / 2; i++)
  {
    for (int j = 0; j < N / 2; j++)
    {
      if (i == j) continue;
      rst += P[v2[i]][v2[j]];
    }
  }

  return rst;
}