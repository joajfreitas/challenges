import sys
from pprint import pprint

def neighbors(pos, map):
    x,y = pos
    L = len(map[0])
    ns = [(x,y) for x,y in [(x-1,y), (x,y-1), (x,y+1), (x+1,y)] if x>=0 and y>=0 and x<L and y<L]

    return ns

def search(pos, map, path):
    L = len(map[0])
    x,y = pos
    if x==L-1 and y==L-1:
        return path

    for n in [n for n in neighbors(pos, map) if n not in path]:
        return search(n, map, path + [pos])



with open(sys.argv[1]) as f:
    lines = f.readlines()

map = [[int(c) for c in line.strip()] for line in lines]

pprint(map)

path = search((0,0), map, [])
print(path)
