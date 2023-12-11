import sys

if __name__ == "__main__":
    lines = sys.stdin.readlines()
    lines = [x.strip() for x in lines]
    seq = lines[0]

    left = {}
    right = {}

    for ln in lines[2:]:
        s = ln.split()
        name = s[0]
        l = s[2][1:-1]
        r = s[3][:-1]
        left[name] = l
        right[name] = r
    
    cur = "AAA"
    i = 0
    while cur != "ZZZ":
        if seq[i%len(seq)] == 'L':
            cur = left[cur]
        else:
            cur = right[cur]
        i += 1
    print(i)
