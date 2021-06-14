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

//using int_t = mppp::integer<1>;

void now(std::atomic<bool>& running);

std::map<int, int> factorint(const int num);

template <int Base, typename T>
T modpow(T exponent, T modulus);

template <typename T>
T pow(T base, T exponent);

template <int N>
int multiplicative_order(int p, const std::map<int, int>& factors);

bool coprime_orders(int p);

int nextprime(int n);