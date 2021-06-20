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

std::map<uint64_t, uint64_t> factorint(const uint64_t num)
{
    auto p1 = static_cast<uint64_t>(num);
    auto a = factors{};
    auto result = std::map<uint64_t, uint64_t>{};
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

uint64_t modpow(uint64_t base, uint64_t exponent, uint64_t modulus) {
    base %= modulus;
    uint64_t result {1};
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

template <uint64_t N>
uint64_t multiplicative_order(uint64_t p, const std::map<uint64_t, uint64_t>& factors)
{
    namespace view = std::ranges::views;
    uint64_t group_order = p - 1;
    uint64_t order {1};
    for (const auto& [P, e] : factors)
    {
        auto exponent = group_order;
        for (const auto f: view::iota(0ull, e + 1))
        {
            if (modpow<N>(exponent, p) not_eq 1)
            {
                uint64_t copy = P;
                //std::cout << pow(P, e - f + 1) << " ";
                //order *= pow(P, e - f + 1);
                
                break;
            }
            exponent /= P;
        }

    }
    return order;
}

uint64_t order(const uint64_t n, uint64_t p) {
    auto factors = factorint(p - 1);
    namespace view = std::ranges::views;
    uint64_t group_order = p - 1;
    uint64_t order {1};
    for (const auto& [P, e] : factors)
    {
        uint64_t exponent = group_order;
        for (const auto f: view::iota(0ull, e + 1))
        {
            if (modpow(n, exponent, p) != 1)
            {
                uint64_t alpha = P;
                uint64_t beta =  e - f + 1;
                //std::cout << pow(alpha, beta) << " ";
                order *= pow(alpha, beta);
                
                break;
            }
            exponent /= P;
        }

    }
    return order;
}

bool coprime_orders(uint64_t p)
{
    const auto factors = factorint(p - 1);
    const auto mo2 = multiplicative_order<2ull>(p, factors);
    const auto mo3 = multiplicative_order<3ull>(p, factors);
    if(1 == std::gcd(mo2, mo3) || p == 599479) std::cout << p << " " << mo2 << " " << mo3 << "\n";
    return 1 == std::gcd(mo2, mo3);
}

// crude first draft. Remember to write something more efficient before merging into main
int nextprime(int n) {
    do {
        ++n;
    } while(factorint(n) != std::map<uint64_t, uint64_t>({{n, 1}}) );
    return n;
}