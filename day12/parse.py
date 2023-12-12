import sys

lines = []
for line in sys.stdin:
    lines.append(line)

print(len(lines))
for line in lines:
    s = line.strip().split()
    print(s[0])
    t = s[1].strip().split(',')
    t = list(map(int, t))
    print(len(t))
    print(*t)
