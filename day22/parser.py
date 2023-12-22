import sys

lines = []
for line in sys.stdin:
    lines.append(line)

print(len(lines))
for line in lines:
    print(line.strip().replace(',', ' ').replace('~', ' '))
