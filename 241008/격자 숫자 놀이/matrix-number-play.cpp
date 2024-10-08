#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include <vector>

#define MAX_NUM 101
using namespace std;

int A[MAX_NUM][MAX_NUM];
// key = num
// value = cnt
unordered_map<int, int> cnt_map;
int row_cnt;
int col_cnt;

int r, c, k;
int ans;

void Input();
void Simulation();
void Operate();
void print();

int main() {
  Input();
  Simulation();

  cout << ans << '\n';
  return 0;
}


void Input() {
  row_cnt = 3;
  col_cnt = 3;

  cin >> r >> c >> k;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      cin >> A[i][j];
    }
  }
}

void Simulation() {
  int turn;
  for (turn = 0; turn < 100; turn++)
  {
    if (A[r - 1][c - 1] == k) break;
    Operate();
    //print();
  }
  if (turn == 100) ans = -1;
  else ans = turn;
}

// unordered_map을 vector로 감싸서 커스텀 솥하기 위한 compare 함수
bool compare(pair<int,int> a, pair<int,int> b) {
  if (a.second == b.second) {
    return a.first < b.first;
  }
  return a.second < b.second;
}

void Operate() {

  if (row_cnt >= col_cnt) {

    int max_len = 0;

    for (int i = 0; i < row_cnt; i++)
    {
      cnt_map.clear();

      // 빈도 수 계산
      for (int j = 0; j < col_cnt; j++) {
        if (A[i][j] == 0) continue;
        cnt_map[A[i][j]]++;
      }
      vector<pair<int, int>> sorting_map(cnt_map.begin(), cnt_map.end());
      // 정렬 수행
      sort(sorting_map.begin(), sorting_map.end(), compare);

      // 0으로 클리어
      for (int j = 0; j < col_cnt; j++)
        A[i][j] = 0;

      int len = 0;
      // 숫자 넣기
      for (int j = 0; j < sorting_map.size(); j++)
      {
        if (j == 50) break;
        A[i][2 * j] = sorting_map[j].first;
        A[i][2 * j + 1] = sorting_map[j].second;
        len += 2;
      }

      if (len > max_len) max_len = len;
    }

    // col_cnt 업데이트
    col_cnt = max_len;
  }
  else {
    // 열 기준
    int max_len = 0;

    for (int j = 0; j < col_cnt; j++)
    {
      cnt_map.clear();

      // 빈도 수 계산
      for (int i = 0; i < row_cnt; i++) {
        if (A[i][j] == 0) continue;
        cnt_map[A[i][j]]++;
      }
      vector<pair<int, int>> sorting_map(cnt_map.begin(), cnt_map.end());
      // 정렬 수행
      sort(sorting_map.begin(), sorting_map.end(), compare);
      
      // 0으로 초기화
      for (int i = 0; i < row_cnt; i++)
        A[i][j] = 0;

      int len = 0;
      // 숫자 넣기
      for (int i = 0; i < sorting_map.size(); i++)
      {
        if (i == 50) break;
        A[2 * i][j] = sorting_map[i].first;
        A[2 * i + 1][j] = sorting_map[i].second;
        len += 2;
      }
      if (len > max_len) max_len = len;
    }

    // row_cnt 업데이트
    row_cnt = max_len;
  }
}

void print() {
  for (int i = 0; i < row_cnt; i++)
  {
    for (int j = 0; j < col_cnt; j++)
    {
      cout << A[i][j] << ' ';
    }
    cout << '\n';
  }
  cout << '\n';
}