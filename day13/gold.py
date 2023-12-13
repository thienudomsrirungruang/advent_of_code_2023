import sys

def transpose(grid):
    return list(map(list, zip(*grid)))

def find_rows(grid):
    n = len(grid)
    ans = []
    for p in range(1, n):
        ok = True
        for i in range(p-1, -1, -1):
            j = 2 * p - i - 1
            if j >= n:
                break
            if grid[i] != grid[j]:
                ok = False
                break
        if ok:
            ans += [p]
    return ans


def replace(str, i, c):
    return str[:i] + c + str[i+1:]

if __name__ == "__main__":
    grids = []
    grid = []
    for line in sys.stdin:
        line = line.strip()
        if(line != ""):
            grid.append(line)
        else:
            grids.append(grid)
            grid = []
    if len(grid) > 0:
        grids.append(grid)
    
    
    ans = 0
    for grid in grids:
        # print(find_rows(grid), find_rows(transpose(grid)))
        # old_ans = 100 * find_rows(grid) + find_rows(transpose(grid))
        old_rows = find_rows(grid)
        old_cols = find_rows(transpose(grid))

        n = len(grid)
        m = len(grid[0])
        ok = False
        good = 0
        for i in range(n):
            for j in range(m):

                grid[i] = replace(grid[i], j, '#' if grid[i][j] == '.' else '.')

                new_rows = find_rows(grid)
                new_cols = find_rows(transpose(grid))

                for k in new_rows:
                    if k not in old_rows:
                        good = 100 * k
                        ok = True
                        # print(i, j, 100 * k)
                        break
                for k in new_cols:
                    if k not in old_cols:
                        good = k
                        ok = True
                        # print(i, j, k)
                        break

                grid[i] = replace(grid[i], j, '#' if grid[i][j] == '.' else '.')
            if ok:
                break
        ans += good
    print(ans)    
