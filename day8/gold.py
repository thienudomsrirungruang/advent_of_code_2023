import sys

import math

if __name__ == "__main__":
    lines = sys.stdin.readlines()
    lines = [x.strip() for x in lines]
    seq = lines[0]

    left = {}
    right = {}
    names = []

    for ln in lines[2:]:
        s = ln.split()
        name = s[0]
        l = s[2][1:-1]
        r = s[3][:-1]
        left[name] = l
        right[name] = r
        names.append(name)
    
    start = [n for n in names if n[-1] == 'A']
    cycles = []
    offsets = []

    for s in start:
        i = 0
        cur = s
        hits = []
        while len(hits) < 2:
            if seq[i%len(seq)] == 'L':
                cur = left[cur]
            else:
                cur = right[cur]
            i += 1
            if cur[-1] == 'Z':
                hits.append(i)
        offsets.append(hits[0])
        cycles.append(hits[1] - hits[0])

    print(cycles, offsets)

    print(math.lcm(*cycles))
    # print(i)
    
    # print(i)

