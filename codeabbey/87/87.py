#!/usr/bin/env python3

class Tree:
    def __init__(self, left, right, payload):
        self.left = left
        self.right = right
        self.payload = payload

    def append(self, payload):
        if payload == self.payload:
            return
        elif payload > self.payload:
            if self.right is None:
                self.right = Tree(None, None, payload)
            else:
                self.right.append(payload)
        elif payload < self.payload:
            if self.left is None:
                self.left = Tree(None, None, payload)
            else:
                self.left.append(payload)

    def __repr__(self):
        s = "("
        if self.left is None:
            s += "-"
        else:
            s += self.left.__repr__()

        s += ","
        s += str(self.payload)
        s += ","

        if self.right is None:
            s += "-"
        else:
            s += self.right.__repr__()

        s += ")"
        return s

    def walk(self):
        xs = []
        if self.left is not None:
            xs += self.left.walk()
        xs.append(self.payload)
        if self.right is not None:
            xs += self.right.walk()
        return xs


import fileinput

n, ns = [line for line in fileinput.input()]

ns = [int(n) for n in ns.split(" ")]
root = Tree(None, None, ns[0])

for n in ns[1:]:
    root.append(n)

print(root)

