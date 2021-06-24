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

//using int_t = mppp::integer<1>;

void now(std::atomic<bool>& running);

std::map<uint64_t, uint64_t> factorint(const uint64_t num);

template <int Base, typename T>
T modpow(T exponent, T modulus);

uint64_t modpow(uint64_t base, uint64_t exponent, uint64_t modulus);

template <typename T>
T pow(T base, T exponent);

template <uint64_t N>
uint64_t multiplicative_order(uint64_t p, const std::map<uint64_t, uint64_t>& factors);

uint64_t order(uint64_t n, uint64_t p);

bool coprime_orders(uint64_t p);

int nextprime(int n);

std::vector<uint64_t> batch(const std::vector<unsigned> &primes, uint64_t min, uint64_t max);