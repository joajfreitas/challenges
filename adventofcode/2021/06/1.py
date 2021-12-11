import sys

with open(sys.argv[1]) as f:
    lines = f.readlines()

days = int(sys.argv[2])
fishes = [int (x) for x in lines[0].split(",")]

for i in range(days):
    print("day", i, len(fishes))
    new_fish = []
    for i in range(len(fishes)):
        if fishes[i] == 0:
            new_fish.append(8)
            fishes[i] = 6
        else:
            fishes[i] -= 1

    fishes += new_fish

print(len(fishes))



