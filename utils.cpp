
#include "utils.h"

void now(std::atomic<bool>& running)
{
    while (running)
    {
        using namespace std::chrono_literals;
        auto timestamp = std::chrono::system_clock::now();
        auto tt = std::chrono::system_clock::to_time_t(timestamp);
        std::cerr << std::put_time(std::localtime(&tt), "%F %T\n");
        std::this_thread::sleep_for(10s);
    }
}

std::map<int_t, int> 
factorint(const int_t num)
{
    auto p1 = num;
    auto result = std::map<int_t, int>{};
    auto f = int_t{2};
    while (f * f <= p1)
    {
        while (p1 % f == 0)
        {
            auto [it, ok] = result.try_emplace(f, 1);
            if (!ok)
            {
                auto& [key, val] = *it;
                val += 1;
            }
            p1 /= f;
        }
        f = mppp::nextprime(f);
    }
    if (p1 not_eq 1)  result.try_emplace(p1, 1);
    return result;
}

template <int Base, typename T>
T modpow(T exponent, T modulus)
{
    auto base = T{Base};
    base %= modulus;
    auto result = T{1};
    while (exponent > 0)
    {
        if (exponent & 1) result = (result * base) % modulus;
        base = (base * base) % modulus;
        exponent >>= 1;
    }
    return result;
}

template <int N>
int_t multiplicative_order(int_t p)
{
    namespace view = std::ranges::views;
    auto factors = factorint(p - 1);
    auto group_order = p - 1;
    auto order = 1;
    for (const auto& [P, e] : factors)
    {
        auto exponent = group_order;
        for (const auto f: view::iota(0, e + 1))
        {
            if (modpow<N>(exponent, p) not_eq 1)
            {
                order *= mppp::pow(P, e - f + 1);
                break;
            }
            mppp::tdiv_q(exponent, exponent, P);
        }

    }
    return order;
}

bool coprime_orders(int_t p)
{
    const auto mo2 = multiplicative_order<2>(p);
    const auto mo3 = multiplicative_order<3>(p);
    return 1 == mppp::gcd(mo2, mo3);
}
