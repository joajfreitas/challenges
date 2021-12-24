import sys
from pprint import pprint

def parse_line(line):
    state, region = line.replace("\n", "").split(" ")
    region = region.split(",")
    region = tuple([tuple([int(x) for x in r.split("=")[1].split("..")]) for r in region])
    state = 1 if state == "on" else 0
    return state, region


with open(sys.argv[1]) as f:
    lines = f.readlines()

lines = [parse_line(line) for line in lines]

def get_count(cube):
    state, region = cube
    x,y,z = region
    return state * abs((x[1] - x[0] + 1) * (y[1] - y[0] + 1) * (z[1] - z[0] + 1))


def overlap_axis(x1,x2):
    x1s, x1f = x1
    x2s, x2f = x2

    if x1s >= x2s and x1f <= x2f:
        return x1s, x1f
    if x1s <= x2s and x1f >= x2f:
        return x2s, x2f
    if x2s >= x1s and x2s < x1f:
        return x2s, x1f
    if x2f < x1s:
        return None
    if x1f < x2s:
        return None
    if x1s >= x2s and x1s <= x2f:
        return x1s, x2f


def overlap(region1, region2):
    x1,y1,z1 = region1
    x2,y2,z2 = region2
    ov1 = overlap_axis(x1,x2)
    if ov1 is None:
        return None
    ov2 = overlap_axis(y1,y2)
    if ov2 is None:
        return None
    ov3 = overlap_axis(z1,z2)
    if ov3 is None:
        return None
    return ov1,ov2,ov3


def count(tally, cube):
    state, region = cube

    aux = []

    if state == 1:
        aux.append(cube)

    for s,r in tally:
        ov = overlap(region, r)
        if ov is None:
            continue

        if s == 1 and state == 0:
            aux.append((-1, ov))
            continue
        if s == -1 and state == 0:
            aux.append((1, ov))
            continue
        if s == 1 and state == 1:
            aux.append((-1, ov))
            continue
        if s == -1 and state == 1:
            aux.append((1, ov))
            continue

    tally += aux

def in_range(cube):
    def in_range_axis(axis):
        #if axis[0] < -50 or axis[0] > 50 or axis[1] < -50 or axis[1] > 50:
        #    return False

        return True
    state, region = cube
    x,y,z = region

    return in_range_axis(x) and in_range_axis(y) and in_range_axis(z)



tally = [lines[0]]
for line in lines[1:]:
    if in_range(line):
        count(tally, line)

pprint(tally)
print(sum([get_count(x) for x in tally]))
