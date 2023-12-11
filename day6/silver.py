time = [41, 66, 72, 66]
distance = [244, 1047, 1228, 1040]
T = 4

tot = 1
for t in range(T):
    ans = 0
    for i in range(0, time[t]+1):
        d = (time[t]-i)*i
        if d > distance[t]:
            ans += 1
    tot *= ans

print(tot)

