import sys

def main():
    elfs = []
    with open(sys.argv[1]) as f:
        lines = f.read().split("\n\n")
        for line in lines:
            calories = line.split("\n")
            elfs.append(sum([int(calory) for calory in calories if calory != ""]))
    
    m1 = max(elfs)
    print(m1)
    elfs.pop(elfs.index(m1))

    m2 = max(elfs)
    elfs.pop(elfs.index(m2))

    m3 = max(elfs)
    elfs.pop(elfs.index(m3))

    print(m1 + m2 + m3)



if __name__ == "__main__":
    main()
