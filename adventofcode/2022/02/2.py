import sys
import enum

class Play(enum.Enum):
    Rock = 0
    Paper = 1
    Scissors = 2

def match(result, enemy):
    rules = [[0,-1,1], [1,0,-1], [-1,1,0]]
    
    return rules[enemy.value].index(-result)

def score(play, result):
    return play + 1 + 3*(result + 1)

def convert(x):
    if x == 'A':
        return Play.Rock
    elif x == 'B':
        return Play.Paper
    elif x == 'C':
        return Play.Scissors

def convert_result(x):
    if x == 'X':
        return -1
    elif x == 'Y':
        return 0
    elif x == 'Z':
        return 1

with open(sys.argv[1]) as f:
    lines =f.readlines()

lines = [line.strip().split(' ') for line in lines]
lines = [(convert_result(result), convert(enemy)) for enemy, result in lines]
lines = [score(match(result, enemy), result) for result, enemy in lines]
print(sum(lines))
