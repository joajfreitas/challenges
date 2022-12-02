import sys
import enum

class Play(enum.Enum):
    Rock = 0
    Paper = 1
    Scissors = 2

def match(first, second):
    rules = [[0,-1,1], [1,0,-1], [-1,1,0]]

    return rules[first.value][second.value]

def score(play, result):
    return play.value + 1 + 3*(result + 1)

def convert(x):
    if x == 'A' or x == 'X':
        return Play.Rock
    elif x == 'B' or x == 'Y':
        return Play.Paper
    elif x == 'C' or x == 'Z':
        return Play.Scissors

with open(sys.argv[1]) as f:
    lines =f.readlines()

lines = [line.strip().split(' ') for line in lines]
lines = [(convert(expected), convert(yours)) for expected, yours in lines]
lines = [score(yours, match(yours, expected)) for expected, yours in lines]
print(sum(lines))
