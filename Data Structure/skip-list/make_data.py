#!/usr/bin/python
import random as rand

n = rand.randint(100000, 100000)
print n
for i in range(n):
    op = rand.randint(0, 2)
    a = rand.randint(1, 10000)
    b = rand.randint(1, 10000)
    print "{} {} {}".format(op, a, b)
