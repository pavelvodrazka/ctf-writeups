#!/usr/bin/env python3

import random
from functools import lru_cache

random.seed(1337)

@lru_cache(100)
def fibonacci(n):
    if n <= 1:
        return 1
    return fibonacci(n - 1) + fibonacci(n - 2)

def fibonacci_seq(n):
    return [ fibonacci(i) for i in range(n) ]

def randonacci(n):
    return n % random.randint(1, n)

randonacci_seq = list(map(randonacci, fibonacci_seq(103)))

print(randonacci_seq[-1])
