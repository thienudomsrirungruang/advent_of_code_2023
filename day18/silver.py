import sys

OFF = -100
N = 201

DIRS = {'L': (0, -1), 'R': (0, 1), 'U': (-1, 0), 'D': (1, 0)}

def cross(a, b):
    return a[0] * b[1] - a[1] * b[0]

if __name__ == "__main__":
    lines = []
    for line in sys.stdin:
        lines.append(line.strip().split())
        
    # grid = [[False] * N for _ in range(N)]
    cur = (0, 0)
    # grid[cur[0]][cur[1]] = True
    area = 0
    perim = 0
    for line in lines:
        dir = DIRS[line[0]]
        num = int(line[1])
        new_cur = (cur[0] + dir[0] * num, cur[1] + dir[1] * num)
        area += cross(cur, new_cur)
        print(cur, new_cur, cross(cur, new_cur))
        cur = new_cur
        perim += num

        # grid[cur[0]][cur[1]] = True
    # print(ans / 2)
    area /= 2
    area = abs(area)
    print(area, perim)
    print(area + perim / 2 + 1)
