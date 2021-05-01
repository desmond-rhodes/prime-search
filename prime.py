#!/usr/bin/env python3.8

prime = []

# range(start, end) does not include end
for i in range(2,101):
	for j in prime:
		if i % j == 0:
			break
	# else after for loop don't execute when exit with break
	else:
		prime.append(i)

print(prime)

print('Hello, world!')
