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

uint64_t mulmod(uint64_t a, uint64_t b, uint64_t m) {
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

uint64_t modpow_two(uint64_t exponent, uint64_t modulus) {
    uint64_t result = 1ull << (exponent % 64);
    if(exponent < 64) return result % modulus;

	uint64_t base = (1 + ~modulus) % modulus;
    exponent >>= 6;

    while (exponent > 0) {
        if (exponent & 1) result = mulmod(result, base, modulus);
        base = mulmod(base, base, modulus);
        exponent >>= 1;
    }
    return result;
}

uint64_t modpow_three(uint64_t exponent, uint64_t modulus) {
    uint64_t base = 3;
    uint64_t result {1};
    while (exponent > 0){
        if (exponent & 1) result = mulmod(result, base, modulus);
        base = mulmod(base, base, modulus);
        exponent >>= 1;
    }
    return result;
}

std::vector<uint64_t> order_two(std::map<uint64_t, uint64_t> factors, uint64_t p) {
    namespace view = std::ranges::views;
    uint64_t group_order = p - 1;
    std::vector<uint64_t> order;
    for (const auto& [P, e] : factors)
    {
        uint64_t exponent = group_order;
        for (const auto f: view::iota(0ull, e + 1))
        {
            if (modpow_two(exponent, p) != 1)
            {
                uint64_t alpha = P;
                order.push_back(alpha);
                
                break;
            }
            exponent /= P;
        }

    }
    return order;
}

bool order_three(std::map<uint64_t, uint64_t> factors, uint64_t p, std::vector<uint64_t> mo2) {
    namespace view = std::ranges::views;
    uint64_t group_order = p - 1;
    std::vector<uint64_t> order;
    for (const auto& [P, e] : factors)
    {
        uint64_t exponent = group_order;
        for (const auto f: view::iota(0ull, e + 1))
        {
            if (modpow_three(exponent, p) != 1)
            {
                uint64_t alpha = P;
                if(std::binary_search(mo2.begin(), mo2.end(), alpha)) return false;
                
                break;
            }
            exponent /= P;
        }

    }
    return true;
}

bool coprime_orders(uint64_t p) {
    if(p == 2 || p == 3) return false;
    const auto factors = factorint(p - 1);
    const auto mo2 = order_two(factors, p);
    
    return  order_three(factors, p, mo2);
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
    for(size_t iter = 1; iter != bools.size(); ++iter) {
        if(bools[iter] && min + iter != 1) out.push_back(min + iter);
    }
    return out;
}