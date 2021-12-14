import sys
from itertools import pairwise
from collections import Counter

def transform(pair, transformations):
    p = "".join(pair)
    if p in transformations.keys():
        return [pair[0], transformations[p]]
    else:
        return [pair[0]]

def insert(polymer, transformations):
    inserted_polymer = []
    for p in pairwise(polymer):
        inserted_polymer += transform(p, transformations)

    inserted_polymer.append(polymer[-1])
    return "".join(inserted_polymer)

with open(sys.argv[1]) as f:
    txt = f.read()

polymer, _, *transformations = txt.split("\n")

transformations = dict([t.split(" -> ") for t in transformations if t != ""])
pairs = Counter(["".join(p) for p in pairwise(polymer)])
chars = Counter(polymer)

for i in range(int(sys.argv[2])):
    for (p1,p2),c in pairs.copy().items():
        t = transformations[p1+p2]
        chars[t] += c
        pairs[p1+p2] -= c
        pairs[p1+t] += c
        pairs[t + p2] += c

print(max(chars.values()) - min(chars.values()))
