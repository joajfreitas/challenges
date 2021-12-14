import sys

with open(sys.argv[1]) as f:
    lines = [line.strip() for line in f.readlines()]


map = []
for line in lines:
    map.append([])
    for c in line:
        map[-1].append(int(c))

def neighbors(x, y):
    idx = [0, 1, -1]
    ns = []
    for i in idx:
        for j in idx:
            if i == 0 and j == 0:
                continue
            ns.append((x+i, y+j))

    return [(i, j) for i, j in ns if i >= 0 and j >= 0 and i <= 9 and j <= 9]


def flatten(map):
    return [item for sublist in map for item in sublist if item > 9]


def flash(x, y, map):
    map[y][x] = 0
    ns = neighbors(x, y)
    for x, y in ns:
        map[y][x] += 1


def simulate(map):
    for y, line in enumerate(map):
        for x, _ in enumerate(line):
            map[y][x] += 1

    flashes = []
    while True:
        if len(flatten(map)) > 0:
            for y, line in enumerate(map):
                for x, v in enumerate(line):
                    if v > 9 and (x, y) not in flashes:
                        flashes.append((x, y))
                        flash(x, y, map)
        else:
            break

    for x, y in flashes:
        map[y][x] = 0

    return map, len(flashes)


s = 0
for t in range(int(sys.argv[2])):
    map, count = simulate(map)
    s += count

print(s)
