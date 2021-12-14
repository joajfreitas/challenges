import sys
from itertools import pairwise
from collections import Counter

def parse_transform(transformation):
    input, out = transformation.split(" -> ")
    return input, out

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

polymer, transformations = txt.split("\n\n")

transformations = dict([parse_transform(transformation) for transformation in transformations.split("\n") if transformation != ""])

for i in range(int(sys.argv[2])):
    polymer = insert(polymer, transformations)

counter = Counter(polymer)
freqs = counter.most_common()
print(freqs[0][1] - freqs[-1][1])
