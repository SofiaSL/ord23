#pragma once

#include <atomic>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <ranges>
#include <thread>
#include <map>
#include <mp++/mp++.hpp>

using int_t = mppp::integer<1>;

void now(std::atomic<bool>& running);

std::map<int_t, int> 
factorint(const int_t num);

template <int Base, typename T>
T modpow(T exponent, T modulus);

template <int N>
int_t multiplicative_order(int_t p, const std::map<int_t, int>& factors);

bool coprime_orders(int_t p);
