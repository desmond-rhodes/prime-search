#include <iostream>
#include <vector>
#include <string>
#include <chrono>

int parse_args(int, char*[], unsigned long long&, unsigned long long, bool&);
void generate_report(
	char,
	unsigned long long,
	std::vector<unsigned long long> const&,
	std::vector<unsigned long long> const&,
	std::chrono::duration<double>
);
void format_duration(std::chrono::duration<double> const&);

int main(int argc, char* argv[]) {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	unsigned long long ceiling;
	bool benchmark;
	if (parse_args(argc, argv, ceiling, 10, benchmark))
		return -1;

	std::vector<unsigned long long> prime {5, 7};
	size_t r {0};
	auto square {prime[r]*prime[r]};

	auto time_0 {std::chrono::steady_clock::now()};

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

	auto time_1 {std::chrono::steady_clock::now()};

	if (prime.back() > ceiling)
		prime.pop_back();

	generate_report(benchmark, ceiling, prime, {2, 3}, time_1-time_0);
	return 0;
}

int parse_args(int argc, char* argv[], unsigned long long& ceiling, unsigned long long min, bool& benchmark) {
	std::vector<std::string> args {argv+1, argv+argc};

	if (args.size() == 2)
		benchmark = (args[0] == "--benchmark");
	else
		benchmark = false;

	if (args.size() < 1 || args.size() > 2 || args.size() == 2 && !benchmark) {
		std::cerr
			<< "usage:\n"
			<< "\t[options] (ceiling)\n"
			<< "\t\tFind primes less than or equal to ceiling.\n"
			<< "options:\n"
			<< "\t--benchmark\n"
			<< "\t\tSilence prime list output, only shows number\n"
			<< "\t\tof primes found and execution time.\n";
		return -1;
	}

	try {
		/* stoull don't throw out_of_range on negative */
		if (args.back()[0] == '-')
			throw -1;
		ceiling = std::stoull(args.back());
	}
	catch (...) {
		std::cerr << "Invalid value for ceiling: " << args.back() << '\n';
		return -1;
	}

	if (ceiling < min) {
		std::cerr << "Minimum ceiling value is " << min << ".\n";
		return -1;
	}

	return 0;
}

void generate_report(
	char mode,
	unsigned long long ceiling,
	std::vector<unsigned long long> const& prime,
	std::vector<unsigned long long> const& constant,
	std::chrono::duration<double> duration
) {
	switch (mode) {
	case 0:
		std::cout << '[';
		for (auto i : constant) {
			std::cout << i;
			if (i != constant.back())
				std::cout << ", ";
		}
		for (auto i : prime)
			std::cout << ", " << i;
		std::cout
			<< "]\n"
			<< "Number of, primes less than or equal to " << ceiling << ", found: " << prime.size()+2 << '\n'
			<< "Time elapsed: ";
		format_duration(duration);
		std::cout << '\n';
		break;
	case 1:
		std::cout << prime.size()+2 << ", ";
		format_duration(duration);
		std::cout << '\n';
		break;
	default:
		std::cout << "No report made.\n";
		break;
	}
}

void format_duration(std::chrono::duration<double> const& duration) {
	auto hours {
		std::chrono::duration_cast<std::chrono::hours>
		(duration)
	};
	auto minutes {
		std::chrono::duration_cast<std::chrono::minutes>
		(duration-hours)
	};
	auto seconds {
		std::chrono::duration_cast<std::chrono::seconds>
		(duration-hours-minutes)
	};
	auto milliseconds {
		std::chrono::duration_cast<std::chrono::milliseconds>
		(duration-hours-minutes-seconds)
	};
	auto microseconds {
		std::chrono::duration_cast<std::chrono::microseconds>
		(duration-hours-minutes-seconds-milliseconds)
	};
	auto nanoseconds {
		std::chrono::duration_cast<std::chrono::duration<double, std::nano>>
		(duration-hours-minutes-seconds-milliseconds-microseconds)
	};
	std::cout
		<< hours.count() << "h "
		<< minutes.count() << "m "
		<< seconds.count() << "s "
		<< milliseconds.count() << "ms "
		<< microseconds.count() << "us "
		<< nanoseconds.count() << "ns";
}
