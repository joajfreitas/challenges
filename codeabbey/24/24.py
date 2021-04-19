#!/usr/bin/env python3


import fileinput

n, ns = [line for line in fileinput.input()]
ns = [int(x) for x in ns.split()]

def neumann_rng(x):
    x = x*x
    return (x // 100) % 10000

soluction  = []

for n in ns:
    seq = [n]
    while True:
        n = neumann_rng(n)
        if n in seq:
            soluction.append(seq.index(n)+4)

            break
        seq.append(n)

print(" ".join([str(s) for s in soluction]))
