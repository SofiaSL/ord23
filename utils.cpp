
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
    auto p1 = static_cast<uint64_t>(num);
    auto a = factors{};
    auto result = std::map<int_t, int>{};
    factor(p1, &a);

    for (unsigned int j = 0; j < a.nfactors; j++)
        result[a.p[j]] = a.e[j];

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
int_t multiplicative_order(int_t p, const std::map<int_t, int>& factors)
{
    namespace view = std::ranges::views;
    auto group_order = p - 1;
    auto order = int_t{1};
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
    const auto factors = factorint(p - 1);
    const auto mo2 = multiplicative_order<2>(p, factors);
    const auto mo3 = multiplicative_order<3>(p, factors);
    return 1 == mppp::gcd(mo2, mo3);
}
