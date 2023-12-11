
import sys

if __name__ == "__main__":
    score = 0
    num_items = [1 for i in range(198)]
    for line in sys.stdin:
        g = line.strip().split()
        n = int(g[1][:-1])-1
        win = list(map(int, g[2:12]))
        my = list(map(int, g[13:]))
        # print(win, my)
        good = 0
        for i in my:
            if i in win:
                good += 1
        # print(g, good)
        for i in range(good):
            num_items[n+i+1] += num_items[n]
        # if good > 0:
        #     score += 2 ** (good-1)
    print(sum(num_items))
