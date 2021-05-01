#!/usr/bin/env python3.8

import sys
from time import perf_counter

if len(sys.argv) != 2:
	print('usage:')
	print('    (ceiling)')
	print('        Find primes less than or equal to ceiling.')
	sys.exit(-1)

try:
	ceiling = int(sys.argv[1])
except:
	print('Fail to parse ceiling ({}) as integer.'.format(sys.argv[1]))
	sys.exit(-2)

if ceiling < 3:
	print('Minimum ceiling value is 3.')
	sys.exit(-3)

prime = [3]
x = 0
square = prime[x]**2

bench_start = perf_counter()

for h in range(6, ceiling+2, 6):
	if square < h:
		x += 1
		square = prime[x]**2
	for i in [h-1, h+1]:
		for j in range(0, x+1):
			if i % prime[j] == 0:
				break
		else:
				prime.append(i)

bench_end = perf_counter()

if prime[-1] > ceiling:
	prime.pop()

prime.insert(0, 2)
print(prime)
print('Number of, primes less than or equal to {0}, found: {1}'.format(ceiling, len(prime)))
print('Time elapsed: {:f}s'.format(bench_end-bench_start))
sys.exit(0)
