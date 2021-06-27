#include <nanobench.h>
#include <atomic>
#include "utils.h"

uint64_t modpow0(uint64_t base, uint64_t exponent, uint64_t modulus) {
    base %= modulus;
    uint64_t result {1};
    while (exponent > 0)
    {
       //if (exponent & 1) result = (result * base) % modulus;
        //base = (base * base) % modulus;
        if (exponent & 1) result = result * base % modulus;
        base = base * base % modulus;
        exponent >>= 1;
    }
    return result;
}

std::vector<uint64_t> order0(std::map<uint64_t, uint64_t> factors, const uint64_t n, uint64_t p) {
    namespace view = std::ranges::views;
    uint64_t group_order = p - 1;
    std::vector<uint64_t> order;
    for (const auto& [P, e] : factors)
    {
        uint64_t exponent = group_order;
        for (const auto f: view::iota(0ull, e + 1))
        {
            if (modpow0(n, exponent, p) != 1)
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

bool coprime_orders0(uint64_t p)
{
    if(p == 2 || p == 3) return false;
    const auto factors = factorint(p - 1);
    const constexpr uint64_t two = 2;
    const auto mo2 = order0(factors, two, p);
    const constexpr uint64_t three = 3;
    const auto mo3 = order0(factors, three, p);
    for(auto n1 : mo2) {
        if(std::binary_search(mo3.begin(), mo3.end(), n1)) {
            return false;
        }
    } 
    return true;
}

std::map<__uint128_t, __uint128_t> factorint1(const __uint128_t num)
{
    __uint128_t p1 {num};
    auto a = factors{};
    auto result = std::map<__uint128_t, __uint128_t>{};
    factor(p1, &a);

    for (unsigned int j = 0; j < a.nfactors; j++)
        result[a.p[j]] = a.e[j];

    return result;
}

__uint128_t modpow1(__uint128_t base, __uint128_t exponent, __uint128_t modulus) {
    base %= modulus;
    __uint128_t result {1};
    while (exponent > 0)
    {
       //if (exponent & 1) result = (result * base) % modulus;
        //base = (base * base) % modulus;
        if (exponent & 1) result = result * base % modulus;
        base = base * base % modulus;
        exponent >>= 1;
    }
    return result;
}

std::vector<__uint128_t> order1(std::map<__uint128_t, __uint128_t> factors, const __uint128_t n, __uint128_t p) {
    namespace view = std::ranges::views;
    __uint128_t group_order = p - 1;
    std::vector<__uint128_t> order;
    for (const auto& [P, e] : factors)
    {
        __uint128_t exponent = group_order;
        for (const auto f: view::iota(0ull, e + 1))
        {
            if (modpow1(n, exponent, p) != 1)
            {
                __uint128_t alpha = P;
                __uint128_t beta =  e - f + 1;
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

bool coprime_orders1(__uint128_t p)
{
    if(p == 2 || p == 3) return false;
    const auto factors = factorint1(p - 1);
    const constexpr __uint128_t two = 2;
    const auto mo2 = order1(factors, two, p);
    const constexpr __uint128_t three = 3;
    const auto mo3 = order1(factors, three, p);
    for(auto n1 : mo2) {
        if(std::binary_search(mo3.begin(), mo3.end(), n1)) {
            return false;
        }
    } 
    return true;
}

uint64_t mulmod2(uint64_t a, uint64_t b, uint64_t m) {
  uint64_t r;
  __asm__
  ( "mulq %2\n\t"
      "divq %3"
      : "=&d" (r), "+%a" (a)
      : "rm" (b), "rm" (m)
      : "cc"
  );
  return r;
}

uint64_t modpow2(uint64_t base, uint64_t exponent, uint64_t modulus) {
    base %= modulus;
    uint64_t result {1};
    while (exponent > 0)
    {
       //if (exponent & 1) result = (result * base) % modulus;
        //base = (base * base) % modulus;
        if (exponent & 1) result = mulmod2(result, base, modulus);
        base = mulmod2(base, base, modulus);
        exponent >>= 1;
    }
    return result;
}

std::vector<uint64_t> order2(std::map<uint64_t, uint64_t> factors, const uint64_t n, uint64_t p) {
    namespace view = std::ranges::views;
    uint64_t group_order = p - 1;
    std::vector<uint64_t> order;
    for (const auto& [P, e] : factors)
    {
        uint64_t exponent = group_order;
        for (const auto f: view::iota(0ull, e + 1))
        {
            if (modpow2(n, exponent, p) != 1)
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

bool coprime_orders2(uint64_t p)
{
    if(p == 2 || p == 3) return false;
    const auto factors = factorint(p - 1);
    const constexpr uint64_t two = 2;
    const auto mo2 = order2(factors, two, p);
    const constexpr uint64_t three = 3;
    const auto mo3 = order2(factors, three, p);
    for(auto n1 : mo2) {
        if(std::binary_search(mo3.begin(), mo3.end(), n1)) {
            return false;
        }
    } 
    return true;
}

uint64_t mulmod3(uint64_t a, uint64_t b, uint64_t m) {
    int64_t res = 0;
    while (a != 0) {
        if (a & 1) res = (res + b) % m;
        a >>= 1;
        b = (b << 1) % m;
    }
    return res;
}

uint64_t modpow3(uint64_t base, uint64_t exponent, uint64_t modulus) {
    base %= modulus;
    uint64_t result {1};
    while (exponent > 0)
    {
       //if (exponent & 1) result = (result * base) % modulus;
        //base = (base * base) % modulus;
        if (exponent & 1) result = mulmod3(result, base, modulus);
        base = mulmod3(base, base, modulus);
        exponent >>= 1;
    }
    return result;
}

std::vector<uint64_t> order3(std::map<uint64_t, uint64_t> factors, const uint64_t n, uint64_t p) {
    namespace view = std::ranges::views;
    uint64_t group_order = p - 1;
    std::vector<uint64_t> order;
    for (const auto& [P, e] : factors)
    {
        uint64_t exponent = group_order;
        for (const auto f: view::iota(0ull, e + 1))
        {
            if (modpow3(n, exponent, p) != 1)
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

bool coprime_orders3(uint64_t p)
{
    if(p == 2 || p == 3) return false;
    const auto factors = factorint(p - 1);
    const constexpr uint64_t two = 2;
    const auto mo2 = order3(factors, two, p);
    const constexpr uint64_t three = 3;
    const auto mo3 = order3(factors, three, p);
    for(auto n1 : mo2) {
        if(std::binary_search(mo3.begin(), mo3.end(), n1)) {
            return false;
        }
    } 
    return true;
}

int main() {

    std::vector<unsigned> primes; // all the primes less than 10^6.5

    for(unsigned n = 2; n != 3'162'277; ++n) {
		if(std::all_of(primes.begin(), primes.end(), [&](int i) {return n % i != 0;})) {
			primes.push_back(n);
		}
	}

    ankerl::nanobench::Bench().run("batch of 10^6 numbers after 10^12 (overflow)", [&] {
        auto v = batch(primes, 1'000'000'000'000ull, 1'000'001'000'000ull);
        for(auto i : v) {
            ankerl::nanobench::doNotOptimizeAway(coprime_orders0(i));
        }
    });

    ankerl::nanobench::Bench().run("batch of 10^6 numbers after 10^12 (128 bit)", [&] {
        auto v = batch(primes, 1'000'000'000'000ull, 1'000'001'000'000ull);
        for(auto i : v) {
            ankerl::nanobench::doNotOptimizeAway(coprime_orders1(i));
        }
    });

    ankerl::nanobench::Bench().run("batch of 10^6 numbers after 10^12 (assembly)", [&] {
        auto v = batch(primes, 1'000'000'000'000ull, 1'000'001'000'000ull);
        for(auto i : v) {
            ankerl::nanobench::doNotOptimizeAway(coprime_orders2(i));
        }
    });

    ankerl::nanobench::Bench().run("batch of 10^6 numbers after 10^12 (peasant)", [&] {
        auto v = batch(primes, 1'000'000'000'000ull, 1'000'001'000'000ull);
        for(auto i : v) {
            ankerl::nanobench::doNotOptimizeAway(coprime_orders3(i));
        }
    });
}