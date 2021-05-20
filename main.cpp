#include "utils.h"
#include "rang.hpp"

int main()
{
    auto counter = int_t{0};
    auto i = int_t{5};
    while (i < 10'000'000'000'000)
    {
        if (coprime_orders(i))
        {
            std::cout << '\n'
                      << rang::fgB::red
                      << i
                      << rang::fg::reset
                      << std::flush;
        }

        i = mppp::nextprime(i);

        if (0 == (++counter % 1000'000))
            std::cout << '.' << std::flush;
    }
}
