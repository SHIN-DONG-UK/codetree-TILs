#include <iostream>
#include <vector>
#include <cstring>

#define MAX_NUM 15
using namespace std;

struct Point {
  int y;
  int x;
};

struct Command{
  int dir;
  int dist;
};

int dy[9] = { 0, 0,-1,-1,-1,0,1,1,1 };
int dx[9] = { 0, 1,1,0,-1,-1,-1,0,1 };

int N, M;
int map[MAX_NUM][MAX_NUM];
int visited[MAX_NUM][MAX_NUM];
vector<Point> v;

void Input();
void Simulation();
void Move(Command cmd);
void Inject();
void Get();
void output();

int main() {
  Input();
  Simulation();
  output();

  return 0;
}

void Input() {
  cin >> N >> M;
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      cin >> map[i][j];
    }
  }
  // 초기 영양제
  v.push_back({ N - 2, 0 });
  v.push_back({ N - 2, 1 });
  v.push_back({ N - 1, 0 });
  v.push_back({ N - 1, 1 });
}

void Simulation() {
  Command cmd;
  for (int i = 0; i < M; i++) {
    cin >> cmd.dir >> cmd.dist;
    Move(cmd);
    Inject();
    Get();
  }
}

void Move(Command cmd) {
  for (int i = 0; i < v.size(); i++) {
    v[i].y = (v[i].y + dy[cmd.dir] * cmd.dist + N) % N;
    v[i].x = (v[i].x + dx[cmd.dir] * cmd.dist + N) % N;
  }
}

void Inject() {
  for (int i = 0; i < v.size(); i++)
  {
    map[v[i].y][v[i].x]++;
    visited[v[i].y][v[i].x] = 1;
  }
  // 대각선 체크
  int ny, nx;
  for (int i = 0; i < v.size(); i++)
  {
    for (int d = 2; d <= 8; d += 2)
    {
      ny = v[i].y + dy[d];
      nx = v[i].x + dx[d];
      if (ny < 0 || ny >= N || nx < 0 || nx >= N) continue;
      if (map[ny][nx] > 0) map[v[i].y][v[i].x]++;
    }
  }
  // 영양제 소멸
  v.clear();
}

void Get() {
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      if (visited[i][j] == 1) continue;
      if (map[i][j] >= 2) {
        map[i][j] -= 2;
        v.push_back({ i,j });
      }
    }
  }
  // 영양제 위치 체크 초기화
  memset(visited, 0, sizeof(visited));
}

void output() {
  int sum = 0;
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      sum += map[i][j];
    }
  }
  cout << sum << '\n';
}