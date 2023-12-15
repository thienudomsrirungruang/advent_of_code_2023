s = input()
x = [x.strip() for x in s.split(',')]
print(len(x))
print(*x, sep='\n')