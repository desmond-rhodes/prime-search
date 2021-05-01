#!/usr/bin/env python3.8

import sys
import time
import math

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

if ceiling < 3:
	print('Minimum ceiling value is 3.')
	sys.exit(-3)

prime = [3]

# start benchmark
bench_start = time.perf_counter()

# range(start, end, step) does not include end
# step = 2 to avoid checking even numbers
for i in range(5, ceiling + 1, 2):
	# test only against factors less than the square root
	root = math.sqrt(i)
	for j in prime:
		if j > root:
			prime.append(i)
			break
		if i % j == 0:
			break

# end of benchmark
bench_end = time.perf_counter()

# prepend 2 to the prime list since it was skipped
prime.insert(0, 2)

print(prime)
print('Number of, primes less than {0}, found: {1}'.format(ceiling, len(prime)))

# benchmark report
print('Time elapsed: {:f}s'.format(bench_end - bench_start))

sys.exit(0)
