#include <iostream>
using namespace std;

int N;
int arr[1000000];
int m1, m2;
long long ans;

void input();
void solve();

int main() {
  input();
  solve();

  cout << ans << '\n';
}

void input() {
  cin >> N;
  for (int i = 0; i < N; i++)
    cin >> arr[i];
  cin >> m1 >> m2;
}

void solve() {
  for (int i = 0; i < N; i++) {
    arr[i] -= m1;
    ans++;
  }
  for (int i = 0; i < N; i++)
  {
    if (arr[i] > 0) {
      ans += arr[i] / m2;
      if (arr[i] % m2 != 0) ans += 1;
    }
  }
    

}