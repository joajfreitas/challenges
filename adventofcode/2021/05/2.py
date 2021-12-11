import sys
with open(sys.argv[1]) as f:
    lines = f.readlines()

def parse_line(line):
    line = line.replace("\n", "")
    fp, sp = line.split("->")
    fp = tuple([int(x) for x in fp.strip().split(",")])
    sp = tuple([int(x) for x in sp.strip().split(",")])
    return fp, sp


def vertical_line(fp, sp):
    f, s = sorted([fp[1], sp[1]])
    for i in range(f, s+1):
        yield (fp[0], i)

def horizontal_line(fp, sp):
    f, s = sorted([fp[0], sp[0]])
    for i in range(f, s+1):
        yield (i, fp[1])

def diagonal_line(fp, sp):
    if (fp[0] > sp[0] and fp[1] < sp[1]) or (fp[0] > sp[0] and fp[1] > sp[1]):
        aux = fp
        fp = sp
        sp = aux

    if fp[0] < sp[0] and fp[1] < sp[1]:
        for i,j in zip(range(fp[0], sp[0]+1), range(fp[1], sp[1]+1)):
            yield i,j
    elif fp[0] < sp[0] and fp[1] > sp[1]:
        for i,j in zip(range(fp[0], sp[0]+1), reversed(range(sp[1], fp[1]+1))):
            yield i,j
    else:
        print("line not in canonical form")
        sys.exit(1)



grid = {}
for line in lines:
    fp, sp = parse_line(line)
    if fp[0] == sp[0]:
        points = vertical_line(fp, sp)
    elif fp[1] == sp[1]:
        points = horizontal_line(fp, sp)
    else:
        points = diagonal_line(fp, sp)


    for point in points:
        if point in grid.keys():
            grid[point] += 1
        else:
            grid[point] = 1


print(len([x for x in grid.values() if x >= 2]))
