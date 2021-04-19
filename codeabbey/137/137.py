#!/usr/bin/env python3


import fileinput
ns, *rest  = [line for line in fileinput.input()]

char_count = {}

for c in ns:
    if c=="\n":
        continue

    char_count[c] = char_count.get(c,0)+1

print(char_count)


def split(char_count):
    total = sum(char_count.values())
    result = []
    s = 0
    for k,v in char_count.items():
        if s > total-s:
            yield result
            total = total-s
            result = []
            s = 0
        else:
            result.append(k)
            s += v

for s in split(char_count):
    print(s)


