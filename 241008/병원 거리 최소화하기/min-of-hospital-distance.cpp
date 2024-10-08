#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_NUM 50
using namespace std;

struct Point {
  int y;
  int x;
};

int N, M;
int map[MAX_NUM][MAX_NUM];
int path[13];
vector<Point> hospitals;
vector<Point> people;
int ans = 1e9;

void Input();
void GetCombination(int cnt, int start);
int Calc();

void print();

int main() {
  Input();
  GetCombination(0, 0);

  cout << ans << '\n';
}

void Input() {
  cin >> N >> M;
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      cin >> map[i][j];
      if (map[i][j] == 2) hospitals.push_back({ i, j });
      else if (map[i][j] == 1) people.push_back({ i, j });
    }
  }
}

void GetCombination(int cnt, int start) {
  if (cnt == M) {
    int tmp = Calc();
    if (ans > tmp) ans = tmp;
    return;
  }
  for (int i = start; i < hospitals.size(); i++)
  {
    path[cnt] = i;
    GetCombination(cnt + 1, i + 1);
  }
}

int Calc() {
  int tmp;
  int rst = 0;
  
  for (int i = 0; i < people.size(); i++)
  {
    int dist = 1e9;
    for (int j = 0; j < M; j++){
      tmp = abs(hospitals[path[j]].y - people[i].y) + abs(hospitals[path[j]].x - people[i].x);
      if (dist > tmp) dist = tmp;
    }
    rst += dist;
  }

  return rst;
}

void print() {
  cout << '\n';
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      cout << map[i][j] << ' ';
    }
    cout << '\n';
  }
  cout << '\n';
}