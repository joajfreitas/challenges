import sys
from pprint import pprint
from queue import PriorityQueue



def enhance(map):
    def increase(line, x):
        aux = []
        for n in line:
            y = (n+x) % 10
            if y != n+x:
                y+=1
            aux.append(y)

        return aux

    enhanced1 = []
    for line in map:
        enhanced1.append(line + increase(line, 1) + increase(line, 2) + increase(line, 3) +  increase(line, 4))

    for j in range(4):
        for i in range(len(map)):
            enhanced1.append(increase(enhanced1[i], j+1))


    return enhanced1


def neighbors(pos, map, w, h):
    x,y = pos

    if x>0:
        yield x-1,y
    if y>0:
        yield x,y-1
    if x < w-1:
        yield x+1,y
    if y < h-1:
        yield x,y+1

def path(map, p, goal):
    acc = 0
    while goal != (0,0):
        x,y = goal
        acc += map[x][y]
        goal = p[goal]

    return acc

def search(map, start, goal):
    pq = PriorityQueue()
    pq.put((0, start))

    ws = {start:0}

    width, height = len(map), len(map[0])

    steps = {start: None}

    while not pq.empty():
        _, pos = pq.get()
        if pos == goal:
            break

        for neighbor in neighbors(pos,map, width, height):
            cost = ws[pos] + map[pos[0]][pos[1]]
            if neighbor not in ws or cost < ws[neighbor]:
                ws[neighbor] = cost
                pq.put((cost,neighbor))
                steps[neighbor] = pos


    return steps


with open(sys.argv[1]) as f:
    lines = f.readlines()

map = [[int(c) for c in line.strip()] for line in lines]
map = enhance(map)
goal = (len(map)-1, len(map[0])-1)
D = search(map, (0,0), goal)
print(path(map, D, goal))
