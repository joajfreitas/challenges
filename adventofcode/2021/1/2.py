import sys

def main(args):
    with open(args[1]) as f:
        lines = f.readlines()

    lines = list(map(lambda x: int(x.strip()), filter(lambda x: x.strip()!='', lines)))
    sums = []

    for i in range(len(lines)-2):
        s = lines[i] + lines[i+1] + lines[i+2]
        sums.append(s)

    print(len(list(filter(lambda x: x>0, (map(lambda x: x[1]-x[0], zip(sums[:-1], sums[1:])))))))


if __name__ == '__main__':
    main(sys.argv)
