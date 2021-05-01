#!/usr/bin/env python3.8

import sys
import time

if len(sys.argv) != 2:
	print('usage:')
	print('    (ceiling)')
	print('        Find primes less than ceiling.')
	sys.exit(-1)

try:
	ceiling = int(sys.argv[1])
except:
	print('Fail to parse ceiling ({}) as integer.'.format(sys.argv[1]))
	sys.exit(-2)

prime = []

# start benchmark
bench_start = time.perf_counter()

# range(start, end) does not include end
for i in range(2, ceiling + 1):
	for j in prime:
		if i % j == 0:
			break
	# else after for loop don't execute when exit with break
	else:
		prime.append(i)

# end of benchmark
bench_end = time.perf_counter()

print(prime)

# benchmark report
print('Time elapsed: {:f}s'.format(bench_end - bench_start))

print('Hello, world!')
sys.exit(0)
