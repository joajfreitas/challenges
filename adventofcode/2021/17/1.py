import sys

from matplotlib import pyplot as plt

def parse(x):
    return tuple([int(v) for v in x[2:].split("..")])

with open(sys.argv[1]) as f:
    coords = f.read().split(": ")[1].replace("\n", "")
    x,y = coords.split(", ")

def trajectory(v, goal):
    x = (0,0)
    xs = [(0,0)]
    reached_goal = False
    for t in range(1000):
        if goal[0][0] <= x[0] and x[0] <= goal[0][1] and goal[1][0] <= x[1] and x[1] <= goal[1][1]:
            reached_goal = True
            break
        if x[0] > goal[0][1] or x[1]<goal[1][0]:
            break
        x = (x[0]+v[0], x[1] + v[1])
        v = (v[0]-1 if v[0] > 0 else 0, v[1]-1)
        xs.append(x)

    return reached_goal, xs

def peak(xs):
    return max([y for x,y in xs])

def print_trajectory(xs):
    x = [x[0] for x in xs]
    y = [x[1] for x in xs]
    plt.scatter(x,y)
    plt.show()


coords = (parse(x), parse(y))

max_bound = coords[0][1], coords[1][1]
min_bound = (0,0)


results = {}
for x in range(min_bound[0], max_bound[0]+1):
    for y in range(-160, 200):
        goal,xs = trajectory((x,y), coords)
        if not goal:
            continue
        results[(x,y)] = peak(xs)

print(len(results))
#print("\n".join([str(x[0])+","+str(x[1]) for x in results.keys()]))
