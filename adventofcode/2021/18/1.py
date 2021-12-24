import sys

with open(sys.argv[1]) as f:
    line = f.readlines()[0]

l = eval(line)

def up(head, path, v):
    aux = head
    print(path)
    for i in path:
        print("up", aux, i)
        aux = aux[i]

    aux += v

def explode(head, l, p, left, right):
    tree = []
    if isinstance(l, int):
        return
    if p not in l:
        explode(head, l[0], p, left, right + [1])
        explode(head, l[1], p, left + [0], right)
    elif p == l[0]:
        print("explode", left, l[1])
        up(head, right, l[0][1])
    else:
        print("explode", l[0], right)

l = [[[[[9,8],1],2],3],4]
explode(l, l, [9,8], [], [])


