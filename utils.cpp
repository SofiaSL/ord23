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

// https://stackoverflow.com/a/12171020
// I need another fix. This just guts the performance
uint64_t mulmod(uint64_t a, uint64_t b, uint64_t m) {
    int64_t res = 0;
    while (a != 0) {
        if (a & 1) res = (res + b) % m;
        a >>= 1;
        b = (b << 1) % m;
    }
    return res;
}

uint64_t modpow(uint64_t base, uint64_t exponent, uint64_t modulus) {
    base %= modulus;
    uint64_t result {1};
    while (exponent > 0)
    {
       //if (exponent & 1) result = (result * base) % modulus;
        //base = (base * base) % modulus;
        if (exponent & 1) result = mulmod(result, base, modulus);
        base = mulmod(base, base, modulus);
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

std::vector<uint64_t> order(std::map<uint64_t, uint64_t> factors, const uint64_t n, uint64_t p) {
    namespace view = std::ranges::views;
    uint64_t group_order = p - 1;
    std::vector<uint64_t> order;
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
                //order *= pow(alpha, beta);
                order.push_back(alpha);
                
                break;
            }
            exponent /= P;
        }

    }
    return order;
}

bool coprime_orders(uint64_t p)
{
    if(p == 2 || p == 3) return false;
    const auto factors = factorint(p - 1);
    const constexpr uint64_t two = 2;
    const auto mo2 = order(factors, two, p);
    const constexpr uint64_t three = 3;
    const auto mo3 = order(factors, three, p);
    for(auto n1 : mo2) {
        if(std::binary_search(mo3.begin(), mo3.end(), n1)) {
            return false;
        }
    } 
    return true;
}

std::vector<uint64_t> batch(const std::vector<unsigned> &primes, uint64_t min, uint64_t max) {
    std::vector<bool> bools(max - min, true);
    for(auto p : primes) {
		uint64_t n = 1 + min / p; 
		while(p * n < max) {
			bools[p * n - min] = false;
			++n;
		}
	}
    std::vector<uint64_t> out;
    for(int iter = 1; iter != bools.size(); ++iter) {
        if(bools[iter] && min + iter != 1) out.push_back(min + iter);
    }
    return out;
}