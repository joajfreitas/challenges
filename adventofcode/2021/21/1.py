import sys

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


def sim(players):
    dice = Dice()
    while True:
        for player in players.keys():
            pos, score = players[player]
            roll1 = dice.roll()
            roll2 = dice.roll()
            roll3 = dice.roll()
            roll = roll1 + roll2 + roll3
            pos = (pos + roll) % 10
            score += pos+1
            players[player] = (pos, score)
            if score >= 1000:
                return [v[1] for p,v in players.items() if p != player][0], dice.rolls

score, rolls = sim(players)
print(score * rolls)
