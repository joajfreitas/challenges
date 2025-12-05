import sys
from itertools import chain


with open(sys.argv[1], 'r') as file:
    def parse(r):
        x = r.split('-')
        return int(x[0]), int(x[1])+1
    ranges = map(parse, file.readline().strip().split(","))

def invalid(r):
    return int(r) if r[:len(r)//2] == r[len(r)//2:] else 0

print(
      sum(chain(*map(lambda r: list(map(lambda x: invalid(str(x)), range(*r))), ranges))))
