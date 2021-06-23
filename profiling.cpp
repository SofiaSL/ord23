#include <nanobench.h>
#include <atomic>
#include "utils.h"

int main() {
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
}