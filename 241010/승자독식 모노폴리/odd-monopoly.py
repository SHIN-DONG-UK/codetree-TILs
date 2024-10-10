def my_print(arr):
    for i in range(len(arr)):
        for j in range(len(arr[0])):
            print(arr[i][j], end=' ')
        print()
    print()

n, m, k = list(map(int, input().split()))
sharks = [[[]] * n for _ in range(n)]
for i in range(n):
    tmp = list(map(int, input().split()))
    for j in range(n):
        if tmp[j] == 0:
            sharks[i][j] = []
        else:
            sharks[i][j] = [tmp[j]]

directions = [0] + list(map(int, input().split()))

smells = [[None] * n for _ in range(n)]

orders = []
for i in range(m):
    tmp = []
    for _ in range(4):
        tmp.append([0] + list(map(int, input().split())))
    if i == 0:
        orders.append([0] + tmp)
    orders.append([0] + tmp)

# dx, dy 정의
# 상, 하, 좌, 우 순서
dx = [111, -1, 1, 0, 0]
dy = [111, 0, 0, -1, 1]

# 각 상어의 위치를 파악할 수 있어야 함
def where_shark(num):
    for i in range(n):
        for j in range(n):
            if len(sharks[i][j]) > 0:
                if sharks[i][j][0] == num:
                    return i, j
    return None

def can_go(num, direction, x, y):
    order_arr = orders[num][direction]
    for i in range(1, 5):
        nx = x + dx[order_arr[i]]
        ny = y + dy[order_arr[i]]
        if nx >= 0 and nx < n and ny >= 0 and ny < n:
            if smells[nx][ny] == None:
                return nx, ny, order_arr[i]

    # 무조건 자기 자신이 왔던 곳이 있음
    for i in range(1, 5):
        nx = x + dx[order_arr[i]]
        ny = y + dy[order_arr[i]]
        if nx >= 0 and nx < n and ny >= 0 and ny < n:
            if smells[nx][ny] != None and smells[nx][ny][0] == num:
                return nx, ny, order_arr[i]

result = 0
fish = m

while True:
    # 자신의 위치에 자신의 냄새를 뿌린다
    for num in range(1, m+1):
        position = where_shark(num)
        if position != None:
            now_x, now_y = position[0], position[1]
            smells[now_x][now_y] = [num, k]

    result += 1
    # 각 상어 위치 갱신
    for num in range(1, m+1):
        position = where_shark(num)
        if position != None:
            prev_x, prev_y = position[0], position[1]
            direction = directions[num]

            tmp = can_go(num, direction, prev_x, prev_y)

            now_x, now_y, directions[num] = tmp
            sharks[prev_x][prev_y] = []
            sharks[now_x][now_y].append(num)

    # 상어 내보내기
    for i in range(n):
        for j in range(n):
            if len(sharks[i][j]) > 0:
                for _ in range(len(sharks[i][j]) - 1):
                    sharks[i][j].pop()
                    fish -= 1

    # smells 업데이트
    for i in range(n):
        for j in range(n):
            if smells[i][j] != None:
                smells[i][j][1] -= 1
                if smells[i][j][1] == 0:
                    smells[i][j] = None

    if fish == 1:
        print(result)
        break
    if result >= 1000:
        print(-1)
        break