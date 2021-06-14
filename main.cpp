#include "utils.h"
#include "rang.hpp"
#include <mutex>
#include <atomic>
#include <vector>
#include <thread>

auto counter = int{0};
//uint64_t i{143'740'658'653};
uint64_t i{5};
std::mutex m_screen;

void primes(int id) {
    while(i < 1'000'000) {
        if (coprime_orders(i)) {
            m_screen.lock();
            std::cout << '\n'
                      << rang::fgB::red
                      << i
                      << rang::fg::reset
                      << std::flush;
            m_screen.unlock();
        }
 
        m_screen.lock();
        i = nextprime(i);
        m_screen.unlock();
 
        if (0 == (++counter % 10'000'000)) {
            m_screen.lock();
            std::cout << '.' << std::flush;
            m_screen.unlock();
        }
    }
}
        
int main()
{
   /*while (i < 1'000'000'000'000)
    {
        if (coprime_orders(i))
        {
            std::cout << '\n'
                      << rang::fgB::red
                      << i
                      << rang::fg::reset
                      << std::flush;
        }

        i = nextprime(i);

        if (0 == (++counter % 10'000'000))
            std::cout << '.' << std::flush;
    }*/
    const constexpr int nthreads {8};
    std::vector<std::thread> threads;
    for(int h = 0; h != nthreads; ++h) {
        std::thread t (primes, h);
        threads.push_back(std::move(t));
    }
    for(auto& thread : threads) {
        thread.join();
    }
}
