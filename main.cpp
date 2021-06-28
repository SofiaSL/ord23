#include "utils.h"
#include "rang.hpp"
#include <mutex>
#include <atomic>
#include <thread>

void thread(const std::vector<uint64_t> &batch) {
    for(auto p : batch) {
        if(coprime_orders(p)) {
            std::cout << '\n'
                      << rang::fgB::red
                      << p
                      << rang::fg::reset
                      << std::flush;
        }
    }
    std::cout << "." << std::flush;
}
        
int main() {
    const constexpr uint64_t ten13halves {3'162'277}; // sqrt(10^13)
    const constexpr uint64_t ten13 {10'000'000'000'000};
    const constexpr uint64_t batch_size {1'000'000'000};

    std::vector<unsigned> primes; // all the primes less than 10^6.5

    for(unsigned n = 2; n != ten13halves; ++n) {
		if(std::all_of(primes.begin(), primes.end(), [&](int i) {return n % i != 0;})) {
			primes.push_back(n);
		}
	}

    for(auto p : primes) {
        if(coprime_orders(p)) {
            std::cout << '\n'
                      << rang::fgB::red
                      << p
                      << rang::fg::reset
                      << std::flush;
        }
    }

    std::vector<std::thread> threads;

    for(uint64_t n = 0; n != 10'000; ++n) {
        auto vector = batch(primes, n * batch_size, (n + 1) * batch_size);
        std::thread t(thread, vector);
        threads.push_back(std::move(t));
    }

    for(auto& thread : threads) {
        thread.join();
    }
}
