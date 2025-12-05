import sys
from itertools import chain


with open(sys.argv[1], 'r') as file:
    def parse(r):
        x = r.split('-')
        return int(x[0]), int(x[1])+1
    ranges = map(parse, file.readline().strip().split(","))

def invalid(r):
    for i in range(1,len(r)//2+1):
        if r == r[:i] * (len(r)//i):
            return int(r)
    return 0

print(
      sum(chain(*map(lambda r: list(map(lambda x: invalid(str(x)), range(*r))), ranges))))
