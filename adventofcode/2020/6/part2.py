import sys

def main():
    with open(sys.argv[1]) as f:
        i = f.read()

    groups = i.split("\n\n")


    rs = []

    for group in groups:
        aux = set("abcdefghijklmnopqrstuvxyzw")
        for line in group.split("\n"):
            if line == "":
                continue
            s = set(line)
            aux = aux.intersection(s)

        rs.append(aux)

    print(sum([len(r) for r in rs]))


if __name__ == '__main__':
    main()
