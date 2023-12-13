import sys

def transpose(grid):
    return list(map(list, zip(*grid)))

def find_rows(grid):
    n = len(grid)
    ans = 0
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
            ans += p
    return ans


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
        ans += 100 * find_rows(grid) + find_rows(transpose(grid))
    print(ans)    
