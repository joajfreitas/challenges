import sys
import random

with open(sys.argv[1]) as f:
    lines = f.readlines()

line = [int(x) for x in lines[0].split(",")]

def cost(line, pos):
    return sum([abs(pos-x) for x in line])

def search(line):
    costs = [(i, cost(line, pos)) for i,pos in enumerate(range(min(line), max(line)))]
    print(min(costs, key=lambda x: x[1]))

search(line)
