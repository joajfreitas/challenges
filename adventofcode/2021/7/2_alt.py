import sys
import random

with open(sys.argv[1]) as f:
    lines = f.readlines()

line = [int(x) for x in lines[0].split(",")]

def cost(line, pos):
    return sum([sum(range(1,abs(pos-x)+1)) for x in line])

def search(line):
    pos = sum(line)/len(line)
    up = round(pos)
    down = int(pos)
    print(cost(line, up))
    print(cost(line, down))

search(line)
