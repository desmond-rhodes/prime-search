#include <iostream>
#include <vector>
#include <string>
#include <chrono>

int main(int argc, char* argv[]) {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::vector<std::string> args {argv+1, argv+argc};

	if (args.size() != 1) {
		std::cerr
			<< "usage:\n"
			<< "\t(ceiling)\n"
			<< "\t\tFind primes less than or equal to ceiling.\n";
		return -1;
	}

	unsigned long long ceiling {0};
	try {
		// stoull don't throw out_of_range on negative
		if (args[0][0] == '-')
			throw -1;
		ceiling = std::stoull(args[0]);
	}
	catch (...) {
		std::cerr << "Invalid value for ceiling: " << args[0] << '\n';
		return -1;
	}

	if (ceiling < 10) {
		std::cerr << "Minimum ceiling value is 10.\n";
		return -1;
	}

	std::vector<unsigned long long> prime {5, 7};
	size_t r {0};
	auto square {prime[r]*prime[r]};

	auto time_s {std::chrono::steady_clock::now()};

	for (unsigned long long i {11}; i <= ceiling; i+=6) {
		for (auto i : {i, i+2}) {
			if (square <= i) {
				++r;
				square = prime[r]*prime[r];
			}
			for (size_t j {0}; j < r; ++j)
				if (i % prime[j] == 0)
					goto skip;
			prime.push_back(i);
			skip:;
		}
	}

	auto time_e {std::chrono::steady_clock::now()};
	std::chrono::duration<double, std::milli> time_d {time_e-time_s};

	if (prime.back() > ceiling)
		prime.pop_back();

	std::cout << "[2, 3";
	for (auto i : prime)
		std::cout << ", " << i;
	std::cout << "]\n";

	std::cout << "Number of, primes less than or equal to " << ceiling << ", found: " << prime.size()+2 << '\n';
	std::cout << "Time elapsed: " << time_d.count() << "ms\n";

	return 0;
}
