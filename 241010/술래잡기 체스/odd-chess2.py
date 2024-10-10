import copy


def my_print(arr):
    for i in range(len(arr)):
        for j in range(len(arr[0])):
            print(arr[i][j], end=' ')
        print()
    print()

MAP = [[None] * 4 for _ in range(4)]
for i in range(4):
    tmp = list(map(int, input().split()))
    for j in range(4):
        MAP[i][j] = [tmp[2*j], tmp[2*j + 1] - 1]

# 방향 정의
dx = [-1, -1, 0, 1, 1, 1, 0, -1]
dy = [0, -1, -1, -1, 0, 1, 1, 1]

def where_fish(arr, num):
    for i in range(len(arr)):
        for j in range(len(arr[0])):
            if arr[i][j][0] == num:
                return i, j
    return None

def turn_left(direction):
    return (direction + 1) % 8

def can_go(x, y, shark_x, shark_y):
    if x >= 0 and x < 4 and y >= 0 and y < 4:
        if not (x == shark_x and y == shark_y):
            return True
    else:
        return False

def move_fishes(arr, shark_x, shark_y):
    for i in range(1, 17):
        pos = where_fish(arr, i)
        if pos != None:
            x, y = pos[0], pos[1]
            direction = arr[x][y][1]
            for _ in range(8):
                nx = x + dx[direction]
                ny = y + dy[direction]
                if can_go(nx, ny, shark_x, shark_y):
                    arr[x][y][1] = direction
                    arr[nx][ny], arr[x][y] = arr[x][y], arr[nx][ny]
                    break
                direction = turn_left(direction)

def posible_position(arr, x, y):
    tmp = []
    for i in range(1, 4):
        nx = x + dx[arr[x][y][1]] * i
        ny = y + dy[arr[x][y][1]] * i
        if nx >= 0 and nx < 4 and ny >= 0 and ny < 4:
            if arr[nx][ny][0] != 0:
                tmp.append([nx, ny])
    return tmp

result = 0
def dfs(arr, now_x, now_y, cost):
    global result
    arr = copy.deepcopy(arr)
    cost += arr[now_x][now_y][0]
    arr[now_x][now_y][0] = 0

    move_fishes(arr, now_x, now_y)

    tmp = posible_position(arr, now_x, now_y)
    if len(tmp) == 0:
        result = max(result, cost)
        return

    for tx, ty in tmp:
        dfs(arr, tx, ty, cost)

dfs(MAP, 0, 0, 0)
print(result)