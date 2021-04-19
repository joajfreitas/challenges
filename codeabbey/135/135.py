#!/usr/bin/env python3

import fileinput
ns, *rest  = [line for line in fileinput.input()]

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


s = ""
for c in ns:
    s += table[c]

words = [s[i: i+8] for i in range(0, len(s), 8)]
if len(words[-1]) < 8:
    words[-1] += '0' * (8-len(words[-1]))

print(" ".join([format(int(word, 2), '02X') for word in words]))
