import sys

with open(sys.argv[1]) as f:
    lines = f.readlines()

x = 0
z = 0

for line in lines:
    direction, distance = line.split(" ")
    if direction == "forward":
        x += int(distance)
    elif direction == "down":
        z += int(distance)
    elif direction == "up":
        z -= int(distance)

print(x,z,x*z)

