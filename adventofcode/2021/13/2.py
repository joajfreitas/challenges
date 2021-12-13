import sys
from pprint import pprint

def parse_dot(dot):
    x,y = dot.split(",")
    return int(x), int(y)

def parse_fold(fold):
    _, _, fold = fold.split(" ")
    axis, idx = fold.split("=")

    return axis, int(idx)

def foldx(dots, idx):
    for x,y in dots:
        if x < idx:
            yield x,y
        else:
            yield idx - (x-idx), y


def foldy(dots, idx):
    for x,y in dots:
        if y < idx:
            yield x,y
        else:
            yield x, idx - (y-idx)

def fold(dots, fold):
    if fold[0] == "x":
        return foldx(dots, fold[1])
    elif fold[0] == "y":
        return foldy(dots, fold[1])
    else:
        assert False

def plot(dots):
    x = [x for x,y in dots]
    y = [y for x,y in dots]

    sizex = max(x)
    sizey = max(y)

    matrix = [["." for i in range(sizex+1)] for j in range(sizey+1)]

    for x,y in dots:
        matrix[y][x] = "#"

    for line in matrix:
        print("".join(line))


with open(sys.argv[1]) as f:
    txt = f.read()

dots, folds = txt.split("\n\n")

dots = [parse_dot(dot) for dot in dots.split("\n")]
folds = [parse_fold(fold) for fold in folds.split("\n") if fold != '']



for f in folds:
    dots = set(fold(dots, f))

plot(dots)
