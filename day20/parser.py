import sys

lines = []
for line in sys.stdin:
    lines.append(line.strip())

print(len(lines))
for line in lines:
    x = line.split("->")
    ty = x[0][0] == '&'
    name = x[0][1:].strip() if x[0][0] in "&%" else x[0].strip()
    out = [n.strip() for n in x[1].split(',')]
    print(1 if ty else 0, name, len(out))
    print(*out)
