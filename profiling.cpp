#include <nanobench.h>
#include <atomic>
#include "utils.h"

int main() {

    std::vector<unsigned> primes; // all the primes less than 10^6.5

    for(unsigned n = 2; n != 3'162'277; ++n) {
		if(std::all_of(primes.begin(), primes.end(), [&](int i) {return n % i != 0;})) {
			primes.push_back(n);
		}
	}

    ankerl::nanobench::Bench().run("orders mod the first 10^5 primes", [&] {
        int c = 0;
        for(uint64_t i = 5; c < 100'000; i = nextprime(i)) {
            //if(coprime_orders(i)) std::cout << i << "\n";
            ankerl::nanobench::doNotOptimizeAway(coprime_orders(i));
            ++c;
        }
    });

    ankerl::nanobench::Bench().run("just factor the first 10^5 primes", [&] {
        int c = 0;
        for(uint64_t i = 5; c < 100'000; i = nextprime(i)) {
            //if(coprime_orders(i)) std::cout << i << "\n";
            ankerl::nanobench::doNotOptimizeAway(factorint(i - 1));
            ++c;
        }
    });

    ankerl::nanobench::Bench().run("just finding the first 10^5 primes", [&] {
        int c = 0;
        for(uint64_t i = 5; c < 100'000; i = nextprime(i)) {
            //if(coprime_orders(i)) std::cout << i << "\n";
            ankerl::nanobench::doNotOptimizeAway(++c);
        }
    });

    ankerl::nanobench::Bench().run("just finding the first 10^5 primes with rainbow table", [&] {
         ankerl::nanobench::doNotOptimizeAway(batch(primes, 1, 100'000));
    });

    ankerl::nanobench::Bench().run("orders mod the first thousand primes greater than 10^12", [&] {
        int c = 0;
        uint64_t i {1'000'000'000'000ull};
        i = nextprime(i);
        for(; c < 1000; i = nextprime(i)) {
            //if(coprime_orders(i)) std::cout << i << "\n";
            ankerl::nanobench::doNotOptimizeAway(coprime_orders(i));
            ++c;
        }
    });

    ankerl::nanobench::Bench().run("just factor the first thousand primes greater than 10^12", [&] {
        int c = 0;
        uint64_t i {1'000'000'000'000ull};
        i = nextprime(i);
        for(; c < 1000; i = nextprime(i)) {
            //if(coprime_orders(i)) std::cout << i << "\n";
            ankerl::nanobench::doNotOptimizeAway(factorint(i - 1));
            ++c;
        }
    });

    ankerl::nanobench::Bench().run("just finding the first thousand primes greater than 10^12", [&] {
        int c = 0;
        uint64_t i {1'000'000'000'000ull};
        i = nextprime(i);
        for(; c < 1000; i = nextprime(i)) {
            //if(coprime_orders(i)) std::cout << i << "\n";
            ankerl::nanobench::doNotOptimizeAway(++c);
        }
    });

    ankerl::nanobench::Bench().run("just finding the first thousand primes greater than 10^12 with rainbow table", [&] {
         ankerl::nanobench::doNotOptimizeAway(batch(primes, 1'000'000'000'000ull, 1'000 + 1'000'000'000'000ull));
    });
}