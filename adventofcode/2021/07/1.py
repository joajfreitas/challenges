import sys
import random

with open(sys.argv[1]) as f:
    lines = f.readlines()

line = [int(x) for x in lines[0].split(",")]

def cost(line, pos):
    return sum([abs(pos-x) for x in line])

def search(line):
    line = sorted(line)
    x = line[len(line)//2]
    print(x, cost(line, x))

search(line)
