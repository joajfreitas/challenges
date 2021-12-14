import sys

with open(sys.argv[1]) as f:
    lines = f.readlines()

days = int(sys.argv[2])
fishes = [int (x) for x in lines[0].split(",")]
fishes = [fishes.count(i) for i in range(9)]

for i in range(days):
    n = fishes.pop(0)
    fishes[6] += n
    fishes.append(n)

print(sum(fishes))



