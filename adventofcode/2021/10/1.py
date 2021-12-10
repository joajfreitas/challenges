import sys

with open(sys.argv[1]) as f:
    lines = f.readlines()


def find_errors(line):
    mapping = {
        "{": "}",
        "(": ")",
        "<": ">",
        "[": "]"
    }

    stack = []

    print(line)
    for c in line:
        print(stack)
        if c in ["{", "(", "<", "["]:
            stack.insert(0,c)
        else:
            o = stack.pop(0)
            if c != mapping[o]:
                print("return", c, o)
                return c

    return 0


scores = {
    ")": 3,
    "]": 57,
    "}": 1197,
    ">": 25137,
    0:0
}

lines = [line.replace("\n", "") for line in lines]
print([find_errors(line) for line in lines])
print(sum([scores[find_errors(line)] for line in lines]))
