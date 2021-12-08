import sys

with open(sys.argv[1]) as f:
    lines = [line.replace("\n", "") for line in f.readlines()]

digits = []

for line in lines:
    _, output = line.split('|')
    output = output[1:].split(" ")
    for segment in output:
        if len(segment) == 2:
            digits.append(1)
        elif len(segment) == 4:
            digits.append(4)
        elif len(segment) == 3:
            digits.append(7)
        elif len(segment) == 7:
            digits.append(8)

print(len(digits))
