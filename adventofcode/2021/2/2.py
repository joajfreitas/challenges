import sys

with open(sys.argv[1]) as f:
    lines = f.readlines()

x = 0
z = 0
aim = 0

for line in lines:
    direction, distance = line.split(" ")
    if direction == "forward":
        x += int(distance)
        z += int(distance) * aim
    elif direction == "down":
        aim += int(distance)
    elif direction == "up":
        aim -= int(distance)

print(x,z,x*z)

