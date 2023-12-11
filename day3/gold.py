import sys

OFFSETS = [(i, j) for i in range(-1, 2) for j in range(-1, 2) if not (i == 0 and j == 0)]

if __name__ == "__main__":
    grid = [line.strip() for line in sys.stdin.readlines()]

    n = len(grid)
    m = len(grid[0])
    
    sum = 0

    gears = [[[] for _ in range(m)] for _ in range(n)]

    for i in range(n):
        for j in range(m):
            if grid[i][j].isdigit() and (j == 0 or not grid[i][j-1].isdigit()):
                number = 0
                x = j
                to_add = set()
                while x < m and grid[i][x].isdigit():
                    number = number * 10 + int(grid[i][x])
                    for off in OFFSETS:
                        if 0 <= i + off[0] < n and 0 <= x + off[1] < m and grid[i + off[0]][x + off[1]] == '*':
                            to_add.add((i + off[0], x + off[1]))
                    x += 1
                for p, q in to_add:
                    gears[p][q].append(number)
    
    for i in range(n):
        for j in range(m):
            if len(gears[i][j]) == 2:
                sum += gears[i][j][0] * gears[i][j][1]

    print(sum)
