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

    for c in line:
        if c in ["{", "(", "<", "["]:
            stack.insert(0,c)
        else:
            o = stack.pop(0)
            if c != mapping[o]:
                return c

    return 0


def complete(line):
    mapping = {
        "{": "}",
        "(": ")",
        "<": ">",
        "[": "]"
    }

    stack = []
    for c in line:
        if c in ["{", "(", "<", "["]:
            stack.insert(0,c)
        else:
            o = stack.pop(0)

    completion = []
    for c in stack:
        completion.append(mapping[c])

    return completion

def calc_score(completion):
    mapping = {
        ")": 1,
        "]": 2,
        "}": 3,
        ">": 4
    }

    score = 0

    for c in completion:
        score *= 5
        score += mapping[c]

    return score

scores = {
    ")": 3,
    "]": 57,
    "}": 1197,
    ">": 25137,
    0:0
}

lines = [line.replace("\n", "") for line in lines]
corrupted = [line  for line in lines if find_errors(line) != 0]
incomplete = [line for line in lines if line not in corrupted]

scores = [calc_score(completion) for completion in [complete(line) for line in incomplete]]
scores = sorted(scores)
print(scores[len(scores)//2])
