import sys

def parse(id):
    def convert_rows(n):
        if n == 'F':
            return 0
        elif n == 'B':
            return 1

    def convert_cols(n):
        if n == 'L':
            return 0
        elif n == 'R':
            return 1

    row = sum([convert_rows(v)<<(6-i) for i,v in enumerate(id[:7])])
    col = sum([convert_cols(v)<<(2-i) for i,v in enumerate(id[7:])])

    return row,col

def main():
    with open(sys.argv[1]) as f:
        i = f.readlines()


    xs = [parse(line.strip()) for line in i]
    passes = set([row*8 + col for row, col in xs])

    all = set(range(2048))

    print(all - passes)




if __name__ == '__main__':
    main()
