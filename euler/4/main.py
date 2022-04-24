from itertools import product


def is_palindrome(s):
    s = str(s)
    return s == s[::-1]


print(
    next(
        filter(
            is_palindrome,
            map(
                lambda x: x[0] * x[1],
                product(reversed(range(900, 999)), reversed(range(900, 999))),
            ),
        )
    )
)
