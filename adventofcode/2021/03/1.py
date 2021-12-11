import sys

with open(sys.argv[1]) as f:
    lines = f.readlines()
    lines = [line.strip() for line in lines]

L = len(lines[0])
results = {L-i-1:0 for i,_ in enumerate(lines[0])}

for line in lines:
    for i,c in enumerate(line):
        if c == "1":
            results[L-i-1] += 1

gamma = 0
epsilon = 0
for k,v in results.items():
    print(k,v)
    if v > len(lines)/2:
        gamma |= 1 << k
    else:
        epsilon |= 1 << k

print(bin(gamma))
print(bin(epsilon))
print(gamma, epsilon, gamma*epsilon)

