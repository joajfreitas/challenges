import sys
from pprint import pprint
from functools import reduce

def low_point(map):
    for y in range(1, len(map)-1):
        for x in range(1,len(map[0])-1):
            if map[y][x-1] > map[y][x] and map[y][x+1] > map[y][x] and map[y-1][x] > map[y][x] and map[y+1][x] > map[y][x]:
                yield x,y

def neighbors(point, map, region):
    x,y,_ = point
    return [(x,y,v) for x,y,v in [
        (x-1,y,map[y][x-1]),
        (x+1,y,map[y][x+1]),
        (x,y-1,map[y-1][x]),
        (x,y+1,map[y+1][x])
    ] if v != 9 and (x,y,v) not in region]

def load_region(point, map, region):
    ns = neighbors(point,map, region)
    region += ns
    for n in ns:
        load_region(n, map, region)

def in_region(point, regions):
    for region in regions:
        if point in region:
            return True

    return False

with open(sys.argv[1]) as f:
    map  = [[9] + [int(x) for x in line.strip()] + [9] for line in f.readlines()]

map.append([9 for i in range(len(map[0]))])
map.insert(0, [9 for i in range(len(map[0]))])

minima = [(x,y,map[y][x]) for x,y in low_point(map)]

regions = []
for point in minima:
    if in_region(point, regions):
        continue
    region = []
    load_region(point, map, region)
    regions.append(region)

print(reduce(lambda x,y: x*y, sorted([len(region) for region in regions])[-3:]))
