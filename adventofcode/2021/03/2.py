import sys

with open(sys.argv[1]) as f:
    lines = f.readlines()
    lines = [line.strip() for line in lines]

def most_common(lines, offset):
    acc = 0
    for line in lines:
        if line[offset] == "1":
            acc +=1

    if acc>=len(lines)/2:
        return 1
    else:
        return 0

def least_common(lines, offset):
    acc = 0
    for line in lines:
        if line[offset] == "1":
            acc +=1

    if acc>=len(lines)/2:
        return 0
    else:
        return 1

def filter_diag(lines, offset, bit):
    return [line for line in lines if int(line[offset]) == bit]

o2 = lines
idx = 0
while True:
    if len(o2) <= 1:
        break
    bit = most_common(o2, idx)
    o2 = filter_diag(o2, idx, bit)
    idx+=1

co2 = lines
idx = 0
while True:
    if len(co2) <= 1:
        break
    bit = least_common(co2, idx)
    co2 = filter_diag(co2, idx, bit)
    idx+=1

print(int(o2[0], 2), int(co2[0], 2))

#L = len(lines[0])
#results = {L-i-1:0 for i,_ in enumerate(lines[0])}
#
#for line in lines:
#    for i,c in enumerate(line):
#        if c == "1":
#            results[L-i-1] += 1
#
#gamma = 0
#epsilon = 0
#for k,v in results.items():
#    print(k,v)
#    if v > len(lines)/2:
#        gamma |= 1 << k
#    else:
#        epsilon |= 1 << k
#
#print(bin(gamma))
#print(bin(epsilon))
#print(gamma, epsilon, gamma*epsilon)
#
