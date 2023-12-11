time = 41667266
distance = 244104712281040

ans = 0
for i in range(0, time+1):
    d = (time-i)*i
    if d > distance:
        ans += 1

print(ans)