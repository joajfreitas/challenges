import sys

with open(sys.argv[1]) as f:
    lines = [line.replace("\n", "") for line in f.readlines()]

digits = []

#segment_counts = {
#    7: [8],
#    6: [0, 6, 9],
#    5: [2, 3, 5],
#    4: [4],
#    3: [7],
#}
#
#segment_mapping = {
#    0: ["a", "b", "c", "e", "f", "g"],
#    1: ["c", "f"],
#    2: ["a", "c", "d", "e", "g"],
#    3: ["a", "c", "d", "f", "g"],
#    4: ["b", "c", "d", "f"],
#    5: ["a", "b", "d", "f", "g"],
#    6: ["a", "b", "d", "f", "e", "g"],
#    7: ["a", "c", "f"],
#    8: ["a", "b", "c", "d", "e", "f", "g"],
#    9: ["a", "b", "c", "d", "f", "g"],
#}
#
#belief = {}

mapping = {
    "abcdfg" : 0,
    "ac" : 1,
    "abdeg" : 2,
    "acdeg" : 3,
    "acef": 4,
    "cdefg" : 5,
    "bcdefg" : 6,
    "acg" : 7,
    "abcdefg": 8,
    "acdefg" : 9
}


#mapping = {
#    "ac": 1,
#    "eacf": 4,
#    "acg": 7,
#    "abcdefg": 8,
#}
#
#mapping = {
#    "abcdeg": 0,
#    "ab": 1,
#    "acdfg": 2,
#    "abcdf": 3,
#    "abef": 4,
#    "bcdef": 5,
#    "bcdefg": 6,
#    "abd": 7,
#    "abcdefg": 8,
#    "abcdef": 9,
#}


acc = 0
for i,line in enumerate(lines):
    print(i)
    _, output = line.split('|')
    aux = 0
    output = output[1:].split(" ")
    for i, segment in enumerate(reversed(output)):
        aux += mapping["".join(sorted(segment))] * 10**i

    acc += aux

print(acc)
