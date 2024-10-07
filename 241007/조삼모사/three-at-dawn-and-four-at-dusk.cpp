#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
int P[20][20];
bool visited[20];

void input();
void go(int idx, int);
int calc();
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
    int diff = calc();
    if (ans > diff) ans = diff;
    return;
  }

  for (int i = start; i < N; i++)
  {
    if (visited[i] == 1) continue;
    visited[i] = 1;
    go(idx + 1, i + 1);
    visited[i] = 0;
  }

}

int calc() {
  int morningSum = 0; int eveningSum = 0;
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      if (i == j) continue;
      if (visited[i] == 1 && visited[j] == 1)
        morningSum += P[i][j];
      if (visited[i] == 0 && visited[j] == 0)
        eveningSum += P[i][j];
    }
  }

  return abs(morningSum - eveningSum);
}