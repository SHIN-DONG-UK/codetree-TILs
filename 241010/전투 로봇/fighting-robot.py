from collections import deque
n = int(input())
MAP = []
for _ in range(n):
    MAP.append(list(map(int, input().split())))

# (bx, by) : 아기상어 위치
bx, by = 0, 0
for i in range(n):
    for j in range(n):
        if MAP[i][j] == 9:
            bx, by = i, j
            MAP[i][j] = 0
            break

BABYSHARK = 2
dx = [-1, 0, 1, 0]
dy = [0, 1, 0, -1]

# 먹을 수 있는 물고기가 있는지 없는지 판단하는 함수
# 있으면 그 좌표 리스트를 반환하도록 해보자
def where(babyshark):
    tmp = []
    for i in range(n):
        for j in range(n):
            if babyshark > MAP[i][j] and MAP[i][j] != 0:
                tmp.append((i, j))
    return tmp

# 물고기를 먹으러 가는 함수
def go(start_x, start_y, arr):
    check = [[-1] * n for _ in range(n)]
    # 최단거리
    q = deque()
    q.append((start_x, start_y))
    check[start_x][start_y] = 0

    while q:
        x, y = q.popleft()
        for i in range(4):
            nx = x + dx[i]
            ny = y + dy[i]
            if nx >= 0 and nx < n and ny >= 0 and ny < n:
                if BABYSHARK >= MAP[nx][ny] and check[nx][ny] == -1:
                    check[nx][ny] = check[x][y] + 1
                    q.append((nx, ny))

    ax, ay = -1, -1
    tmp = int(1e9)
    # 물고기 선택
    # 이렇게 선택하면 가장 위에 왼쪽 물고기를 선택할 수 있음
    for i in range(n):
        for j in range(n):
            if (i, j) in arr and check[i][j] != -1 and tmp > check[i][j]:
                tmp = check[i][j]
                ax, ay = i, j
    return ax, ay, check[ax][ay]

cnt = 0
ans = 0
while True:
    fishes = where(BABYSHARK)
    if len(fishes) == 0:
        break

    else:
        go_x, go_y, time = go(bx, by, fishes)
        if go_x == -1 and go_y == -1:
            break
        else:
            cnt += 1
            if BABYSHARK == cnt:
                BABYSHARK += 1
                cnt = 0
            MAP[go_x][go_y] = 0
            bx, by = go_x, go_y
            ans += time

print(ans)