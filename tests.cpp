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


/*TEST_CASE( "factorint", "[factorint]" ) {

    using Map = std::map<int, int>;
    REQUIRE( factorint(int{2}) == Map({{2, 1}}) );
    REQUIRE( factorint(int{3}) == Map({{3, 1}}) );
    REQUIRE( factorint(int{4}) == Map({{2, 2}}) );
    REQUIRE( factorint(int{5}) == Map({{5, 1}}) );
    REQUIRE( factorint(int{6}) == Map({{2, 1}, {3, 1}}) );
    REQUIRE( factorint(int{7}) == Map({{7, 1}}) );
    REQUIRE( factorint(int{8}) == Map({{2, 3}}) );
    REQUIRE( factorint(int{9}) == Map({{3, 2}}) );

    REQUIRE( factorint(int{10}) == Map({{2, 1}, {5, 1}}) );
    REQUIRE( factorint(int{11}) == Map({{11, 1}}) );
    REQUIRE( factorint(int{12}) == Map({{2, 2}, {3, 1}}) );
    REQUIRE( factorint(int{13}) == Map({{13, 1}}) );
    REQUIRE( factorint(int{14}) == Map({{2, 1}, {7, 1}}) );
    REQUIRE( factorint(int{15}) == Map({{3, 1}, {5, 1}}) );
    REQUIRE( factorint(int{16}) == Map({{2, 4}}) );
    REQUIRE( factorint(int{17}) == Map({{17, 1}}) );
    REQUIRE( factorint(int{18}) == Map({{2, 1}, {3, 2}}) );
    REQUIRE( factorint(int{19}) == Map({{19, 1}}) );
    REQUIRE( factorint(int{20}) == Map({{2, 2}, {5, 1}}) );

    REQUIRE( factorint(int{100}) == Map({{2, 2}, {5, 2}}) );
    REQUIRE( factorint(int{101}) == Map({{101, 1}}) );
    REQUIRE( factorint(int{102}) == Map({{2, 1}, {3, 1}, {17, 1}}) );
    REQUIRE( factorint(int{103}) == Map({{103, 1}}) );
    REQUIRE( factorint(int{104}) == Map({{2, 3}, {13, 1}}) );
    REQUIRE( factorint(int{105}) == Map({{3, 1}, {5, 1}, {7, 1}}) );
    REQUIRE( factorint(int{106}) == Map({{2, 1}, {53, 1}}) );
    REQUIRE( factorint(int{107}) == Map({{107, 1}}) );
    REQUIRE( factorint(int{108}) == Map({{2, 2}, {3, 3}}) );
    REQUIRE( factorint(int{109}) == Map({{109, 1}}) );
    REQUIRE( factorint(int{110}) == Map({{2, 1}, {5, 1}, {11, 1}}) );

    REQUIRE( factorint(int{1000}) == Map({{2, 3}, {5, 3}}) );
    REQUIRE( factorint(int{1001}) == Map({{7, 1}, {11, 1}, {13, 1}}) );
    REQUIRE( factorint(int{1002}) == Map({{2, 1}, {3, 1}, {167, 1}}) );
    REQUIRE( factorint(int{1003}) == Map({{17, 1}, {59, 1}}) );
    REQUIRE( factorint(int{1004}) == Map({{2, 2}, {251, 1}}) );
    REQUIRE( factorint(int{1005}) == Map({{3, 1}, {5, 1}, {67, 1}}) );
    REQUIRE( factorint(int{1006}) == Map({{2, 1}, {503, 1}}) );
    REQUIRE( factorint(int{1007}) == Map({{19, 1}, {53, 1}}) );
    REQUIRE( factorint(int{1008}) == Map({{2, 4}, {3, 2}, {7, 1}}) );
    REQUIRE( factorint(int{1009}) == Map({{1009, 1}}) );
    REQUIRE( factorint(int{1010}) == Map({{2, 1}, {5, 1}, {101, 1}}) );

    REQUIRE( factorint(int{9777}) == Map({{3, 1}, {3259, 1}}) );
    REQUIRE( factorint(int{9778}) == Map({{2, 1}, {4889, 1}}) );
    REQUIRE( factorint(int{9779}) == Map({{7, 1}, {11, 1}, {127, 1}}) );
    REQUIRE( factorint(int{9780}) == Map({{2, 2}, {3, 1}, {5, 1}, {163, 1}}) );
    REQUIRE( factorint(int{9781}) == Map({{9781, 1}}) );
    REQUIRE( factorint(int{9782}) == Map({{2, 1}, {67, 1}, {73, 1}}) );
    REQUIRE( factorint(int{9783}) == Map({{3, 2}, {1087, 1}}) );
    REQUIRE( factorint(int{9784}) == Map({{2, 3}, {1223, 1}}) );
    REQUIRE( factorint(int{9785}) == Map({{5, 1}, {19, 1}, {103, 1}}) );
    REQUIRE( factorint(int{9786}) == Map({{2, 1}, {3, 1}, {7, 1}, {233, 1}}) );
    REQUIRE( factorint(int{9787}) == Map({{9787, 1}}) );

    REQUIRE( factorint(int{1234567}) == Map({{127, 1}, {9721, 1}}) );
    REQUIRE( factorint(int{2345678}) == Map({{2, 1}, {23, 1}, {50993, 1}}) );
    REQUIRE( factorint(int{500008})  == Map({{2, 3}, {62501, 1}}) );
}

TEST_CASE( "modpow", "[modpow]" ) {

    REQUIRE( modpow<2>(int{18}, int{35}) == 29 );
    REQUIRE( modpow<2>(int{300}, int{35}) == 1 );
    REQUIRE( modpow<2>(int{5000}, int{35}) == 11 );
    REQUIRE( modpow<2>(int{18}, int{45}) == 19 );
    REQUIRE( modpow<2>(int{300}, int{45}) == 1 );
    REQUIRE( modpow<2>(int{5000}, int{45}) == 31 );
    REQUIRE( modpow<2>(int{18}, int{450}) == 244 );
    REQUIRE( modpow<2>(int{300}, int{450}) == 226 );
    REQUIRE( modpow<2>(int{5000}, int{450}) == 76 );
    REQUIRE( modpow<2>(int{18}, int{9001}) == 1115 );
    REQUIRE( modpow<2>(int{300}, int{9001}) == 2838 );
    REQUIRE( modpow<2>(int{5000}, int{9001}) == 4111 );

    REQUIRE( modpow<3>(int{18}, int{35}) == 29 );
    REQUIRE( modpow<3>(int{300}, int{35}) == 1 );
    REQUIRE( modpow<3>(int{5000}, int{35}) == 16 );
    REQUIRE( modpow<3>(int{18}, int{45}) == 9 );
    REQUIRE( modpow<3>(int{300}, int{45}) == 36 );
    REQUIRE( modpow<3>(int{5000}, int{45}) == 36 );
    REQUIRE( modpow<3>(int{18}, int{450}) == 189 );
    REQUIRE( modpow<3>(int{300}, int{450}) == 351 );
    REQUIRE( modpow<3>(int{5000}, int{450}) == 351 );
    REQUIRE( modpow<3>(int{18}, int{9001}) == 8448 );
    REQUIRE( modpow<3>(int{300}, int{9001}) == 2038 );
    REQUIRE( modpow<3>(int{5000}, int{9001}) == 3798 );

}

TEST_CASE( "multiplicative_order", "[multiplicative_order]" ) {

    {
        const auto p = 113; 
        const auto factors = factorint(p - 1);
        REQUIRE( multiplicative_order<2>(p, factors) == 28 );
        REQUIRE( multiplicative_order<3>(p, factors) == 112 );
    }

    {
        const auto p = 683;
        const auto factors = factorint(p - 1);
        REQUIRE( multiplicative_order<2>(p, factors) == 22 );
        REQUIRE( multiplicative_order<3>(p, factors) == 31 );
        REQUIRE( std::gcd(int{22}, int{31}) == 1 );
    }
}*/
