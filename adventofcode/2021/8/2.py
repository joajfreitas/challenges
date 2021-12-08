import sys

def subset(s1, s2):
    i = True
    for s in s1:
        if s not in s2:
            i = False

    return i


def solve(input, output):
    input = ["".join(sorted(word)) for word in input]
    output = ["".join(sorted(word)) for word in output]

    mapping = {
        2: list(filter(lambda x:len(x) == 2, input)),
        3: list(filter(lambda x:len(x) == 3, input)),
        4: list(filter(lambda x:len(x) == 4, input)),
        5: list(filter(lambda x:len(x) == 5, input)),
        6: list(filter(lambda x:len(x) == 6, input)),
        7: list(filter(lambda x:len(x) == 7, input))
    }

    encoding = {
        1 : mapping[2][0],
        7 : mapping[3][0],
        4 : mapping[4][0],
        8 : mapping[7][0],
    }

    encoding[3] = list(filter(lambda x: subset(encoding[1], x), mapping[5]))[0]
    mapping[5].remove(encoding[3])
    encoding[6] = list(filter(lambda x: not subset(encoding[1], x), mapping[6]))[0]
    mapping[6].remove(encoding[6])
    encoding[5] = list(filter(lambda x: subset(x, encoding[6]), mapping[5]))[0]
    mapping[5].remove(encoding[5])
    encoding[2] = mapping[5][0]
    encoding[9] = list(filter(lambda x: subset(encoding[5], x), mapping[6]))[0]
    mapping[6].remove(encoding[9])
    encoding[0] = mapping[6][0]

    decoding = {v:k for k,v in encoding.items()}

    print(mapping)
    print(encoding)
    print(decoding)

    return sum([decoding[word] * 10**i for i,word in enumerate(reversed(output))])

with open(sys.argv[1]) as f:
    lines = [line.replace("\n", "") for line in f.readlines()]

acc = 0
for line in lines:
    input, output = line.split('|')
    s = solve(input[:-1].split(" "), output[1:].split(" "))
    acc += s

print(acc)
