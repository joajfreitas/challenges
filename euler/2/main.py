from functools import cache
from itertools import takewhile


@cache
def fibonnaci(x):
    if x == 0:
        return 1
    elif x == 1:
        return 1
    else:
        return fibonnaci(x - 1) + fibonnaci(x - 2)


def even(x):
    return x % 2 == 0


print(sum(filter(even, takewhile(lambda x: x < 4e6, map(fibonnaci, range(int(4e6)))))))
