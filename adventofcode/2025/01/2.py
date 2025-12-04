import sys
from itertools import accumulate

with open(sys.argv[1]) as f:
    lines = f.readlines()

xs = [50]
for line in lines:
    d = {"L": -1, "R": 1}[line[0]]
    r = int(line[1:])
    xs += abs(r) * [d]

print(sum(map(lambda x: x%100 == 0, accumulate(xs))))
