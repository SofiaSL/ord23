#include "utils.h"
#include "rang.hpp"
#include <mutex>
#include <atomic>
#include <thread>

std::atomic<int> finished_threads {0};
std::mutex counter;

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
    counter.lock();
    ++finished_threads;
    counter.unlock();
}
        
int main() {
    const constexpr uint64_t ten13halves {3'162'277}; // sqrt(10^13)
    const constexpr uint64_t ten13 {10'000'000'000'000};
    const constexpr uint64_t batch_size {1'000'000'000};

    const constexpr int n_threads {4};

    std::vector<unsigned> primes; // all the primes less than 10^6.5

    for(unsigned n = 2; n != ten13halves; ++n) {
		if(std::all_of(primes.begin(), primes.end(), [&](int i) {return n % i != 0;})) {
			primes.push_back(n);
		}
	}

    std::vector<std::thread> threads;

    for(uint64_t n = 0; n != 10'000; ++n) {
        while(n - finished_threads > n_threads) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10'000));
        }
        auto vector = batch(primes, n * batch_size, (n + 1) * batch_size);
        std::thread t(thread, vector);
        threads.push_back(std::move(t));
    }
}
