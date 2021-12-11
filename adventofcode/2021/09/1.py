import sys

with open(sys.argv[1]) as f:
    map  = [[9] + [int(x) for x in line.strip()] + [9] for line in f.readlines()]

map.append([9 for i in range(len(map[0]))])
map.insert(0, [9 for i in range(len(map[0]))])

#print(map)

def low_point(map):
    for y in range(1, len(map)-1):
        for x in range(1,len(map[0])-1):
            if map[y][x-1] > map[y][x] and map[y][x+1] > map[y][x] and map[y-1][x] > map[y][x] and map[y+1][x] > map[y][x]:
                yield y,x


points = list(low_point(map))
print(sum([map[y][x] + 1 for y,x in points]))

