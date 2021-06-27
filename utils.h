#pragma once

#include <atomic>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <ranges>
#include <thread>
#include <map>
//#include <mp++/mp++.hpp>
#include "factor.h"
#include <numeric>
#include <vector>
#include <algorithm>

//using int_t = mppp::integer<1>;

void now(std::atomic<bool>& running);

std::map<uint64_t, uint64_t> factorint(const uint64_t num);

uint64_t mulmod(uint64_t a, uint64_t b, uint64_t m);

uint64_t modpow_two(uint64_t exponent, uint64_t modulus);

uint64_t modpow_three(uint64_t exponent, uint64_t modulus);

std::vector<uint64_t> order_two(std::map<uint64_t, uint64_t> factors, uint64_t p);

bool order_three(std::map<uint64_t, uint64_t> factors, uint64_t p, std::vector<uint64_t> mo2);

bool coprime_orders(uint64_t p);

std::vector<uint64_t> batch(const std::vector<unsigned> &primes, uint64_t min, uint64_t max);