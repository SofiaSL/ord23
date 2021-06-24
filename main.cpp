#include "utils.h"
#include "rang.hpp"
#include <mutex>
#include <atomic>
#include <thread>

auto counter = int{0};
//uint64_t i{143'740'658'653};
uint64_t i{5};
std::mutex m_screen;

void primes(int id) {
    while(i < 50'000) {
        m_screen.lock();
        //m_screen.unlock();
        if(coprime_orders(i)) {
            //m_screen.lock();
            /*std::cout << '\n'
                      << rang::fgB::red
                      << i
                      << rang::fg::reset
                      << std::flush;*/
            //m_screen.unlock();
        }
 
        //m_screen.lock();
        i = nextprime(i);
       // m_screen.unlock();
 
        if(0 == (++counter % 10'000'000)) {
            //m_screen.lock();
            std::cout << '.' << std::flush;
            //m_screen.unlock();
        }
        m_screen.unlock();
        /*m_screen.lock();
        const auto factors = factorint(i - 1);
        const auto mo2 = multiplicative_order<2>(i, factors);
        std::cout << i << " " << mo2 <<  "\n";
        m_screen.unlock();

        m_screen.lock();
        i = nextprime(i);
        m_screen.unlock();*/
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
    /*const constexpr int nthreads {8};
    std::vector<std::thread> threads;
    for(int h = 0; h != nthreads; ++h) {
        std::thread t (primes, h);
        threads.push_back(std::move(t));
    }
    for(auto& thread : threads) {
        thread.join();
    }*/
    const constexpr uint64_t ten13halves {3'162'277}; // sqrt(10^13)
    const constexpr uint64_t ten13 {10'000'000'000'000};
    const constexpr uint64_t batch_size {100'000'000};

    std::vector<unsigned> primes; // all the primes less than 10^6.5

    for(unsigned n = 2; n != ten13halves; ++n) {
		if(std::all_of(primes.begin(), primes.end(), [&](int i) {return n % i != 0;})) {
			primes.push_back(n);
		}
	}

    int c = 0;
    for(i = nextprime(1'000'000); c < 1000; i = nextprime(i)) {
        if(coprime_orders(i)) std::cout << i << "\n";
        ++c;
    }
}
