#!/usr/bin/env python3

table = {
' ': '11',
't': '1001',
'n': '10000',
's': '0101',
'r': '01000',
'd': '00101',
'!': '001000',
'c': '000101',
'm': '000011',
'g': '0000100',
'b': '0000010',
'v': '00000001',
'k': '0000000001',
'q': '000000000001',
'e': '101',
'o': '10001',
'a': '011',
'i': '01001',
'h': '0011',
'l': '001001',
'u': '00011',
'f': '000100',
'p': '0000101',
'w': '0000011',
'y': '0000001',
'j': '000000001',
'x': '00000000001',
'z': '000000000000',
}


decoding = {v: k for k, v in table.items()}

base32 = { "0": 0, "1": 1, "2": 2, "3": 3, "4": 4, "5": 5, "6": 6, "7": 7, "8":
         8, "9": 9, "A": 10, "B": 11, "C": 12, "D": 13, "E": 14, "F": 15, "G":
         16, "H": 17, "I": 18, "J": 19, "K": 20, "L": 21, "M": 22, "N": 23,
         "O": 24, "P": 25, "Q": 26, "R": 27, "S": 28, "T": 29, "U": 30, "V": 31
         }

import fileinput
ns, *rest  = [line for line in fileinput.input()]

ss = ""
for char in ns:
    if char == "\n":
        continue
    ss += format(base32[char], "05b")

buffer = ""
solved = ""

for s in ss:
    buffer += s
    if buffer in decoding.keys():
        solved += decoding[buffer]
        buffer = ""

print(solved)


