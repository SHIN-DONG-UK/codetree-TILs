#include <iostream>
using namespace std;

struct Task {
  int t;
  int p;
};

int N;
Task tasks[15];
int ans;

void input();
void go(int idx, int sum);

int main() {
  input();
  go(0, 0);

  cout << ans << '\n';
}

void input() {
  cin >> N;
  for (int i = 0; i < N; i++)
  {
    cin >> tasks[i].t;
    cin >> tasks[i].p;
  }
}

void go(int idx, int sum) {
  if (idx < N) {
    if (sum > ans) ans = sum;
  }
  else if (idx == N) {
    if (sum > ans) ans = sum;
    return;
  }
  if (idx > N) return;

  go(idx + 1, sum);
  go(idx + tasks[idx].t, sum + tasks[idx].p);

}