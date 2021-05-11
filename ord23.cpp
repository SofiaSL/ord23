// compile with g++ ord23.cpp -o ord23 -std=c++17 -O3 -lpthread

#include <iostream>
#include <numeric>

#include <thread>

#include <vector>
#include <algorithm>

template <class T>
T ord(T n, T p) { // multiplicative order of n mod p
	T counter = 1;
	T copy = n;
	while(copy != 1) {
		copy *= n;
		copy %= p;
		++counter;
	}
	return counter;
}

bool is_prime(uint64_t number){

    if(number < 2) return false;
    if(number == 2) return true;
    if(number % 2 == 0) return false;
    for(int i = 3; i * i <=number; i += 2){
        if(number % i == 0 ) return false;
    }
    return true;

}

void thread(int n) {// check the primes congruent to 2n+1 mod 16
	for(uint64_t i = 16 + 2 * n + 1; i != 100'000'000; i += 16) {
		if(n == 0 && i % 1'048'576 == 1) std::cout << i << "\n";
		if(!is_prime(i)) continue;
		if(std::gcd(ord(2ull,i),ord(3ull,i)) == 1) 
			std::cout << i  << " " << ord(2ull,i) << " " << ord(3ull,i) << "\n";
	}
}

std::vector<uint64_t> factors(uint64_t n) { // all the prime factors of n with multiplicity
	std::vector<uint64_t> out;
	for(uint64_t f = 2; f * f <= n; ++f) {
		while(n % f == 0) {
			out.push_back(f);
			n /= f;
		}
	}
	if(n != 1) out.push_back(n);
	return out;
}

std::vector<uint64_t> factors2(uint64_t n) { // all the prime factors of n without multiplicity
	std::vector<uint64_t> out;
	for(uint64_t f = 2; f * f <= n; ++f) {
		bool done = false;
		while(n % f == 0) {
			if(!done) out.push_back(f);
			done = true;
			n /= f;
		}
	}
	if(n != 1) out.push_back(n);
	return out;
}

template<typename T, typename Pred> typename std::vector<T>::iterator
insert_sorted(std::vector<T> & vec, T const& item, Pred pred) {
    return vec.insert(std::upper_bound(vec.begin(), vec.end(), item, pred), item);
}

template<typename T> typename std::vector<T>::iterator
insert_sorted(std::vector<T> & vec, T const& item) {
    return vec.insert(std::upper_bound(vec.begin(), vec.end(), item), item);
}

std::vector<uint64_t> divisors(uint64_t n) { // all the divisors of n with multiplicity
	auto f = factors(n);
	
	uint64_t a = f[0];
	int counter = 0;
	int ndivisors = 1;
	f.push_back(0);
	for(auto b : f) {
		if(a == b) {
			++counter;
		} else {
			ndivisors *= counter + 1;
			counter = 1;
		}
		a = b;
	}
	f.pop_back();
	
	std::vector<uint64_t> out {1};
	out.reserve(ndivisors);
	
	for(auto k : f) {
		auto end = out.end();
		for(auto a = out.begin(); a != end; ++a) {
			if(n == 12 && *a * k == 12) std::cout << "yyet\n";
			if(!std::binary_search(out.begin(), out.end(), *a * k)) {
				insert_sorted(out, *a * k);
			}
		}
	}
	out.back() = n;
	return out;
}

template <class T>
T ord2(T n, T p) { // multiplicative order of n mod p
	auto f = factors(p - 1);
}

template <class T>
T powmod(T x, T n, T p) { // x^n mod p
  if (n == 0) return 1;
  if (n == 1) return x % p;
  
  T tmp = powmod(x, n / 2, p);
  
  if (n % 2 == 0) return (tmp * tmp) % p;
  return (x * tmp * tmp) % p;
}

bool coprime_orders(uint64_t p) { // returns whether gcd(ord_p(2),ord_p(3))==1
	auto f = divisors(p - 1);
	for(auto iter = f.rbegin(); iter != f.rend(); ++iter) {
		/*if(p == 683 || p == 599479) std::cout << p << " " << *iter << " " << powmod(2ull, (p - 1) / *iter, p) << " " << powmod(3ull, (p - 1) / *iter, p) << "\n";
		if((powmod(2ull, (p - 1) / *iter, p) == 1 && powmod(3ull, (p - 1) / *iter, p) != 1) ||
		   (powmod(2ull, (p - 1) / *iter, p) != 1 && powmod(3ull, (p - 1) / *iter, p) == 1)) {
			return true;
		}*/
		//if(p == 683 || p == 599479) std::cout << p << " " << *iter << " " << powmod(2ull, *iter, p) << " " << powmod(3ull, (p - 1) / *iter, p) << "\n";
		if(powmod(2ull, *iter, p) == 1 && powmod(3ull, (p - 1) / *iter, p) == 1) return true;
	}
	return false;
}

int main() {
	/*std::thread t0(thread, 0);
	std::thread t1(thread, 1);
	std::thread t2(thread, 2);
	std::thread t3(thread, 3);
	std::thread t4(thread, 4);
	std::thread t5(thread, 5);
	std::thread t6(thread, 6);
	std::thread t7(thread, 7);
	
	t0.join();
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();*/
	/*uint64_t s2 = 0;
	uint64_t s3 = 0;
	for(int i = 5; i != 100; ++i) {
		if(!is_prime(i)) continue;
		s2 += ord(2,i);
		s3 += ord(3,i);
		std::cout << i << " " << ord(2,i) << " " << ord(3,i) << "\n";
	}
	std::cout << s2 << " " << s3 << "\n";*/
	for(uint64_t i = 5; i != 1'000'000'000; ++i) {
		if(i % 1'000'000 == 0) std::cout << i << "\n";
		if(!is_prime(i)) continue;
		if(coprime_orders(i)) std::cout << i << "\n";
	}
}