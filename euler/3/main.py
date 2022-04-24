import math
from functools import cache


@cache
def is_prime(x):
    return len(list(filter(lambda i: x % i == 0, range(2, int(math.sqrt(x)))))) == 0


n = 600851475143
*_, last = filter(lambda i: n % i == 0 and is_prime(i), range(2, int(math.sqrt(n))))
print(last)
