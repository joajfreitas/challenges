import sys
from functools import cache

def parse_player(player):
    return int(player.split(":")[1][1:].strip())-1

with open(sys.argv[1]) as f:
    players = f.readlines()

class Dice():
    def __init__(self):
        self.dice = 0
        self.rolls = 0

    def roll(self):
        self.rolls += 1
        self.dice  = (self.dice  % 100) + 1

        return self.dice

players = [parse_player(player) for player in players]

players = {i:(player, 0) for i,player in enumerate(players)}
print(players)

counts = [ (3,1), (4,3), (5,6), (6,7), (7,6), (8,3), (9,1) ]

@cache
def step(player1, player2, player, n):
    #print(player1, player2, player, n)
    win1, win2 = 0,0
    if player == 0:
        pos, score = player1
        pos = (pos + n) % 10
        score += pos + 1
        if score>=21:
            return 1,0
        else:
            for v,c in counts:
                player1 = (pos,score)
                w1, w2 = step(player1, player2, 1, v)
                win1 += w1*c
                win2 += w2*c

            return win1, win2
    else:
        pos, score = player2
        pos = (pos + n) % 10
        score += pos + 1
        if score>=21:
            return 0,1
        else:
            for v,c in counts:
                player2 = (pos,score)
                w1, w2 = step(player1, player2, 0, v)
                win1 += w1*c
                win2 += w2*c

            return win1, win2


def sim(players):
    s1, s2 = 0, 0
    for v,c in counts:
        win1, win2 = step(players[0], players[1], 0, v)
        s1 += win1*c
        s2 += win2*c

    return s1, s2

print(max(list(sim(players))))
