import sys
from functools import reduce
from math import floor, ceil

with open(sys.argv[1]) as f:
    lines = f.readlines()

lines = list(map(eval, lines))

class Explode:
    def __init__(self, pair):
        self.pair = pair

    def get(self):
        return self.pair

    def __repr__(self):
        return f"Explode({self.pair})"


def left_add(tree, value):
    if isinstance(tree, int):
        return tree + value
    else:
        return [left_add(tree[0], value), tree[1]]

def right_add(tree, value):
    if isinstance(tree, int):
        return tree + value
    else:
        return [tree[0], right_add(tree[1], value)]

def explode(tree, depth=1):
    if isinstance(tree, int):
        return False, 0, tree, 0
    left, right = tree

    if depth > 4:
        return True, left, 0, right

    exploded, l, exploded_tree, r = explode(left, depth+1)
    if exploded:
        return True, l, [exploded_tree, left_add(right, r)], 0
    
    exploded, l, exploded_tree, r = explode(right, depth+1)
    if exploded:
        return True, 0, [right_add(left, l), exploded_tree], r

    return False, 0, tree, 0

def split(tree):
    if isinstance(tree, int):
        if tree >= 10:
            return True, [floor(tree/2), ceil(tree/2)]
        else:
            return False, tree

    left, right = tree

    splitted, left_split = split(left)
    if splitted:
        return True, [left_split, right]

    splitted, right_split = split(right)
    if splitted:
        return True, [left, right_split]

    return False, tree

def snailfish_reduce(tree, depth=0):
    while True:
        exploded, _, tree, _ = explode(tree)
        if exploded:
            continue

        splitted, tree = split(tree)
        if not splitted:
            return tree
        
def add(a,b):
    tree = [a, b]
    return snailfish_reduce(tree)

def magnitude(tree):
    if isinstance(tree, int):
        return tree

    left, right = tree
    return 3*magnitude(left) + 2*magnitude(right)


print(magnitude(reduce(add, lines)))
print(max([magnitude(reduce(add, [a,b]))for a in lines for b in lines if a != b]))
