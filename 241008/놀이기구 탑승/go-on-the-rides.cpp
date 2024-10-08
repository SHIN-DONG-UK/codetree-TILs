#include <iostream>

#define MAX_NUM 20
using namespace std;

struct Point {
  int y;
  int x;
};

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

int n;
int map[MAX_NUM][MAX_NUM];
int like_table[MAX_NUM*MAX_NUM + 1][4];
int score_table[5] = { 0,1,10,100,1000 };
int ans;

void Input();
void Simulation();
Point ChooseSeat(int student_num);
void GetScore();

int main() {
  Input();
  Simulation();
  GetScore();

  cout << ans << '\n';
}

void Input() {
  cin >> n;
}

void Simulation() {
  int student_num;
  Point p;
  for (int i = 0; i < n*n; i++) {
    cin >> student_num;

    for (int j = 0; j < 4; j++)
      cin >> like_table[student_num][j];
    p = ChooseSeat(student_num);
    map[p.y][p.x] = student_num;
  }
}

Point ChooseSeat(int student_num) {
  Point rst, np;
  
  int max_like_cnt = -1;
  int max_blank_cnt = -1;

  for (int i = 0; i < n; i++) 
  {
    for (int j = 0; j < n; j++) 
    {
      if (map[i][j] > 0) continue;

      int like_cnt = 0;
      int blank_cnt = 0;
      
      for (int d = 0; d < 4; d++)
      {
        np = { i + dy[d], j + dx[d] };
        if (np.y < 0 || np.y >= n || np.x < 0 || np.x >= n) continue;
        
        // LikeTable에서 해당 친구 찾기
        for (int k = 0; k < 4; k++)
        {
          if (like_table[student_num][k] == map[np.y][np.x])
          {
            like_cnt++;
            break;
          }
        }
        if (map[np.y][np.x] == 0) blank_cnt++;
      }
      // 4 방향 좋아하는 친구 수, 빈칸 수 완료
      // 업데이트
      if (like_cnt > max_like_cnt || (like_cnt == max_like_cnt && blank_cnt > max_blank_cnt)) {
        rst = { i, j };
        max_like_cnt = like_cnt;
        max_blank_cnt = blank_cnt;
      }

    }
  }

  return rst;
}

void GetScore() {
  int cnt = 0;
  Point np;

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      cnt = 0;
      for (int d = 0; d < 4; d++)
      {
        np = { i + dy[d], j + dx[d] };
        if (np.y < 0 || np.y >= n || np.x < 0 || np.x >= n) continue;

        // LikeTable에서 해당 친구 찾기
        for (int k = 0; k < 4; k++)
        {
          if (like_table[map[i][j]][k] == map[np.y][np.x])
          {
            cnt++;
            break;
          }
        }
       
      }

      ans += score_table[cnt];

    }
  }
}