def multiple(x, n):
    return x % n == 0


multiple3 = lambda x: multiple(x, 3)
multiple5 = lambda x: multiple(x, 5)
multiple3or5 = lambda x: multiple3(x) or multiple5(x)


print(sum(filter(multiple3or5, range(1000))))
