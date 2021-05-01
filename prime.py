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

if ceiling < 2:
	print('Minimum ceiling value is 2.')
	sys.exit(-3)

prime = []

# start benchmark
bench_start = time.perf_counter()

# range(start, end, step) does not include end
# step = 2 to avoid checking even numbers
for i in range(3, ceiling + 1, 2):
	for j in prime:
		if i % j == 0:
			break
	# else after for loop don't execute when exit with break
	else:
		prime.append(i)

# end of benchmark
bench_end = time.perf_counter()

# prepend 2 to the prime list since it was skipped
prime.insert(0, 2)

print(prime)
print('Number of, primes less than {0}, found: {1}'.format(ceiling, len(prime)))

# benchmark report
print('Time elapsed: {:f}s'.format(bench_end - bench_start))

sys.exit(0)
