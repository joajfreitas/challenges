m = {}

for i in range(1,4):
    for j in range(1,4):
        for k in range(1,4):
            print(i,j,k)
            s = i+j+k
            if m.get(s):
                m[s] += 1
            else:
                m[s] = 1

print(m)
print(sum(m.values()))
