#!/usr/bin/env python3

import fileinput

n, ns = [line for line in fileinput.input()]

ns = [int(x) for x in ns.split(" ")]
print(sum(ns))
