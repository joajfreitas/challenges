import sys
from pprint import pprint

def parse_line(line):
    state, region = line.replace("\n", "").split(" ")
    region = region.split(",")
    region = tuple([tuple([int(x) for x in r.split("=")[1].split("..")]) for r in region])

    return state, region

def region_to_cubes(region):
    for i in range(region[0][0], region[0][1]+1):
        if i < -50 or i > 50:
            continue
        for j in range(region[1][0], region[1][1]+1):
            if j < -50 or j>50:
                continue
            for k in range(region[2][0], region[2][1]+1):
                if k < -50 or k > 50:
                    continue
                yield i,j,k

with open(sys.argv[1]) as f:
    lines = f.readlines()

lines = [parse_line(line) for line in lines]

print(lines)

map = {}

def apply(map, cubes, state):
    for cube in cubes:
        if cube not in map.keys():
            if state == "on":
                map[cube] = state
        else:
            map[cube] = state


for state,region in lines:
    apply(map, region_to_cubes(region), state)

print(len([x for x in map.values() if x == "on"]))
