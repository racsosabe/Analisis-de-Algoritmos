v = [int(x) for x in input().split()]
x = 0
for i in range(len(v)):
    x = 10 * x + v[i]

print(x)
