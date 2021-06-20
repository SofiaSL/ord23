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

std::map<int, int> factorint(const int num)
{
    auto p1 = static_cast<uint64_t>(num);
    auto a = factors{};
    auto result = std::map<int, int>{};
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

template <typename T>
T pow(T base, T exponent)
{
    auto result = T{1};
    while (exponent > 0)
    {
        if (exponent & 1) result = (result * base);
        base = (base * base);
        exponent >>= 1;
    }
    return result;
}

template <int N>
int multiplicative_order(int p, const std::map<int, int>& factors)
{
    namespace view = std::ranges::views;
    auto group_order = p - 1;
    auto order = int{1};
    for (const auto& [P, e] : factors)
    {
        auto exponent = group_order;
        for (const auto f: view::iota(0, e + 1))
        {
            if (modpow<N>(exponent, p) not_eq 1)
            {
                order *= pow(P, e - f + 1);
                break;
            }
            exponent /= P;
        }

    }
    return order;
}

bool coprime_orders(int p)
{
    const auto factors = factorint(p - 1);
    const auto mo2 = multiplicative_order<2>(p, factors);
    const auto mo3 = multiplicative_order<3>(p, factors);
    return 1 == std::gcd(mo2, mo3);
}

// crude first draft. Remember to write something more efficient before merging into main
int nextprime(int n) {
    do {
        ++n;
    } while(factorint(n).size() != 1);
    return n;
}