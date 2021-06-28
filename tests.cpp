#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "utils.h"

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


TEST_CASE( "factorint", "[factorint]" ) {

    using Map = std::map<uint64_t, uint64_t>;
    REQUIRE( factorint(2) == Map({{2, 1}}) );
    REQUIRE( factorint(3) == Map({{3, 1}}) );
    REQUIRE( factorint(4) == Map({{2, 2}}) );
    REQUIRE( factorint(5) == Map({{5, 1}}) );
    REQUIRE( factorint(6) == Map({{2, 1}, {3, 1}}) );
    REQUIRE( factorint(7) == Map({{7, 1}}) );
    REQUIRE( factorint(8) == Map({{2, 3}}) );
    REQUIRE( factorint(9) == Map({{3, 2}}) );

    REQUIRE( factorint(10) == Map({{2, 1}, {5, 1}}) );
    REQUIRE( factorint(11) == Map({{11, 1}}) );
    REQUIRE( factorint(12) == Map({{2, 2}, {3, 1}}) );
    REQUIRE( factorint(13) == Map({{13, 1}}) );
    REQUIRE( factorint(14) == Map({{2, 1}, {7, 1}}) );
    REQUIRE( factorint(15) == Map({{3, 1}, {5, 1}}) );
    REQUIRE( factorint(16) == Map({{2, 4}}) );
    REQUIRE( factorint(17) == Map({{17, 1}}) );
    REQUIRE( factorint(18) == Map({{2, 1}, {3, 2}}) );
    REQUIRE( factorint(19) == Map({{19, 1}}) );
    REQUIRE( factorint(20) == Map({{2, 2}, {5, 1}}) );

    REQUIRE( factorint(100) == Map({{2, 2}, {5, 2}}) );
    REQUIRE( factorint(101) == Map({{101, 1}}) );
    REQUIRE( factorint(102) == Map({{2, 1}, {3, 1}, {17, 1}}) );
    REQUIRE( factorint(103) == Map({{103, 1}}) );
    REQUIRE( factorint(104) == Map({{2, 3}, {13, 1}}) );
    REQUIRE( factorint(105) == Map({{3, 1}, {5, 1}, {7, 1}}) );
    REQUIRE( factorint(106) == Map({{2, 1}, {53, 1}}) );
    REQUIRE( factorint(107) == Map({{107, 1}}) );
    REQUIRE( factorint(108) == Map({{2, 2}, {3, 3}}) );
    REQUIRE( factorint(109) == Map({{109, 1}}) );
    REQUIRE( factorint(110) == Map({{2, 1}, {5, 1}, {11, 1}}) );

    REQUIRE( factorint(1000) == Map({{2, 3}, {5, 3}}) );
    REQUIRE( factorint(1001) == Map({{7, 1}, {11, 1}, {13, 1}}) );
    REQUIRE( factorint(1002) == Map({{2, 1}, {3, 1}, {167, 1}}) );
    REQUIRE( factorint(1003) == Map({{17, 1}, {59, 1}}) );
    REQUIRE( factorint(1004) == Map({{2, 2}, {251, 1}}) );
    REQUIRE( factorint(1005) == Map({{3, 1}, {5, 1}, {67, 1}}) );
    REQUIRE( factorint(1006) == Map({{2, 1}, {503, 1}}) );
    REQUIRE( factorint(1007) == Map({{19, 1}, {53, 1}}) );
    REQUIRE( factorint(1008) == Map({{2, 4}, {3, 2}, {7, 1}}) );
    REQUIRE( factorint(1009) == Map({{1009, 1}}) );
    REQUIRE( factorint(1010) == Map({{2, 1}, {5, 1}, {101, 1}}) );

    REQUIRE( factorint(9777) == Map({{3, 1}, {3259, 1}}) );
    REQUIRE( factorint(9778) == Map({{2, 1}, {4889, 1}}) );
    REQUIRE( factorint(9779) == Map({{7, 1}, {11, 1}, {127, 1}}) );
    REQUIRE( factorint(9780) == Map({{2, 2}, {3, 1}, {5, 1}, {163, 1}}) );
    REQUIRE( factorint(9781) == Map({{9781, 1}}) );
    REQUIRE( factorint(9782) == Map({{2, 1}, {67, 1}, {73, 1}}) );
    REQUIRE( factorint(9783) == Map({{3, 2}, {1087, 1}}) );
    REQUIRE( factorint(9784) == Map({{2, 3}, {1223, 1}}) );
    REQUIRE( factorint(9785) == Map({{5, 1}, {19, 1}, {103, 1}}) );
    REQUIRE( factorint(9786) == Map({{2, 1}, {3, 1}, {7, 1}, {233, 1}}) );
    REQUIRE( factorint(9787) == Map({{9787, 1}}) );

    REQUIRE( factorint(1234567) == Map({{127, 1}, {9721, 1}}) );
    REQUIRE( factorint(2345678) == Map({{2, 1}, {23, 1}, {50993, 1}}) );
    REQUIRE( factorint(500008) == Map({{2, 3}, {62501, 1}}) );
}

TEST_CASE( "modpow", "[modpow]" ) {

    REQUIRE( modpow_two(18, 35) == 29 );
    REQUIRE( modpow<2>(300, 35) == 1 );
    REQUIRE( modpow<2>(5000, 35) == 11 );
    REQUIRE( modpow<2>(18, 45) == 19 );
    REQUIRE( modpow<2>(300, 45) == 1 );
    REQUIRE( modpow<2>(5000, 45) == 31 );
    REQUIRE( modpow<2>(18, 450) == 244 );
    REQUIRE( modpow<2>(300, 450) == 226 );
    REQUIRE( modpow<2>(5000, 450) == 76 );
    REQUIRE( modpow<2>(18, 9001) == 1115 );
    REQUIRE( modpow<2>(300, 9001) == 2838 );
    REQUIRE( modpow<2>(5000, 9001) == 4111 );

    REQUIRE( modpow<3>(18, 35) == 29 );
    REQUIRE( modpow<3>(300, 35) == 1 );
    REQUIRE( modpow<3>(5000, 35) == 16 );
    REQUIRE( modpow<3>(18, 45) == 9 );
    REQUIRE( modpow<3>(300, 45) == 36 );
    REQUIRE( modpow<3>(5000, 45) == 36 );
    REQUIRE( modpow<3>(18, 450) == 189 );
    REQUIRE( modpow<3>(300, 450) == 351 );
    REQUIRE( modpow<3>(5000, 450) == 351 );
    REQUIRE( modpow<3>(18, 9001) == 8448 );
    REQUIRE( modpow<3>(300, 9001) == 2038 );
    REQUIRE( modpow<3>(5000, 9001) == 3798 );

}

TEST_CASE( "multiplicative_order", "[multiplicative_order]" ) {

    {
        const auto p = 113; 
        const auto factors = factorint(p - 1);
        REQUIRE( order_two(factors, p) == std::vector<uint64_t>{2, 7} );
    }

    {
        const auto p = 683;
        const auto factors = factorint(p - 1);
        REQUIRE( order_two(factors, p) == std::vector<uint64_t>{2, 11} );
        REQUIRE( std::gcd(int{22}, int{31}) == 1 );
    }
}
