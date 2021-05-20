#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "utils.h"

TEST_CASE( "factorint", "[factorint]" ) {

    using Map = std::map<int_t, int>;
    REQUIRE( factorint(int_t{2}) == Map({{2, 1}}) );
    REQUIRE( factorint(int_t{3}) == Map({{3, 1}}) );
    REQUIRE( factorint(int_t{4}) == Map({{2, 2}}) );
    REQUIRE( factorint(int_t{5}) == Map({{5, 1}}) );
    REQUIRE( factorint(int_t{6}) == Map({{2, 1}, {3, 1}}) );
    REQUIRE( factorint(int_t{7}) == Map({{7, 1}}) );
    REQUIRE( factorint(int_t{8}) == Map({{2, 3}}) );
    REQUIRE( factorint(int_t{9}) == Map({{3, 2}}) );

    REQUIRE( factorint(int_t{10}) == Map({{2, 1}, {5, 1}}) );
    REQUIRE( factorint(int_t{11}) == Map({{11, 1}}) );
    REQUIRE( factorint(int_t{12}) == Map({{2, 2}, {3, 1}}) );
    REQUIRE( factorint(int_t{13}) == Map({{13, 1}}) );
    REQUIRE( factorint(int_t{14}) == Map({{2, 1}, {7, 1}}) );
    REQUIRE( factorint(int_t{15}) == Map({{3, 1}, {5, 1}}) );
    REQUIRE( factorint(int_t{16}) == Map({{2, 4}}) );
    REQUIRE( factorint(int_t{17}) == Map({{17, 1}}) );
    REQUIRE( factorint(int_t{18}) == Map({{2, 1}, {3, 2}}) );
    REQUIRE( factorint(int_t{19}) == Map({{19, 1}}) );
    REQUIRE( factorint(int_t{20}) == Map({{2, 2}, {5, 1}}) );

    REQUIRE( factorint(int_t{100}) == Map({{2, 2}, {5, 2}}) );
    REQUIRE( factorint(int_t{101}) == Map({{101, 1}}) );
    REQUIRE( factorint(int_t{102}) == Map({{2, 1}, {3, 1}, {17, 1}}) );
    REQUIRE( factorint(int_t{103}) == Map({{103, 1}}) );
    REQUIRE( factorint(int_t{104}) == Map({{2, 3}, {13, 1}}) );
    REQUIRE( factorint(int_t{105}) == Map({{3, 1}, {5, 1}, {7, 1}}) );
    REQUIRE( factorint(int_t{106}) == Map({{2, 1}, {53, 1}}) );
    REQUIRE( factorint(int_t{107}) == Map({{107, 1}}) );
    REQUIRE( factorint(int_t{108}) == Map({{2, 2}, {3, 3}}) );
    REQUIRE( factorint(int_t{109}) == Map({{109, 1}}) );
    REQUIRE( factorint(int_t{110}) == Map({{2, 1}, {5, 1}, {11, 1}}) );

    REQUIRE( factorint(int_t{1000}) == Map({{2, 3}, {5, 3}}) );
    REQUIRE( factorint(int_t{1001}) == Map({{7, 1}, {11, 1}, {13, 1}}) );
    REQUIRE( factorint(int_t{1002}) == Map({{2, 1}, {3, 1}, {167, 1}}) );
    REQUIRE( factorint(int_t{1003}) == Map({{17, 1}, {59, 1}}) );
    REQUIRE( factorint(int_t{1004}) == Map({{2, 2}, {251, 1}}) );
    REQUIRE( factorint(int_t{1005}) == Map({{3, 1}, {5, 1}, {67, 1}}) );
    REQUIRE( factorint(int_t{1006}) == Map({{2, 1}, {503, 1}}) );
    REQUIRE( factorint(int_t{1007}) == Map({{19, 1}, {53, 1}}) );
    REQUIRE( factorint(int_t{1008}) == Map({{2, 4}, {3, 2}, {7, 1}}) );
    REQUIRE( factorint(int_t{1009}) == Map({{1009, 1}}) );
    REQUIRE( factorint(int_t{1010}) == Map({{2, 1}, {5, 1}, {101, 1}}) );

    REQUIRE( factorint(int_t{9777}) == Map({{3, 1}, {3259, 1}}) );
    REQUIRE( factorint(int_t{9778}) == Map({{2, 1}, {4889, 1}}) );
    REQUIRE( factorint(int_t{9779}) == Map({{7, 1}, {11, 1}, {127, 1}}) );
    REQUIRE( factorint(int_t{9780}) == Map({{2, 2}, {3, 1}, {5, 1}, {163, 1}}) );
    REQUIRE( factorint(int_t{9781}) == Map({{9781, 1}}) );
    REQUIRE( factorint(int_t{9782}) == Map({{2, 1}, {67, 1}, {73, 1}}) );
    REQUIRE( factorint(int_t{9783}) == Map({{3, 2}, {1087, 1}}) );
    REQUIRE( factorint(int_t{9784}) == Map({{2, 3}, {1223, 1}}) );
    REQUIRE( factorint(int_t{9785}) == Map({{5, 1}, {19, 1}, {103, 1}}) );
    REQUIRE( factorint(int_t{9786}) == Map({{2, 1}, {3, 1}, {7, 1}, {233, 1}}) );
    REQUIRE( factorint(int_t{9787}) == Map({{9787, 1}}) );

    REQUIRE( factorint(int_t{1234567}) == Map({{127, 1}, {9721, 1}}) );
    REQUIRE( factorint(int_t{2345678}) == Map({{2, 1}, {23, 1}, {50993, 1}}) );
    REQUIRE( factorint(int_t{500008})  == Map({{2, 3}, {62501, 1}}) );
}

TEST_CASE( "modpow", "[modpow]" ) {

    REQUIRE( modpow<2>(int_t{18}, int_t{35}) == 29 );
    REQUIRE( modpow<2>(int_t{300}, int_t{35}) == 1 );
    REQUIRE( modpow<2>(int_t{5000}, int_t{35}) == 11 );
    REQUIRE( modpow<2>(int_t{18}, int_t{45}) == 19 );
    REQUIRE( modpow<2>(int_t{300}, int_t{45}) == 1 );
    REQUIRE( modpow<2>(int_t{5000}, int_t{45}) == 31 );
    REQUIRE( modpow<2>(int_t{18}, int_t{450}) == 244 );
    REQUIRE( modpow<2>(int_t{300}, int_t{450}) == 226 );
    REQUIRE( modpow<2>(int_t{5000}, int_t{450}) == 76 );
    REQUIRE( modpow<2>(int_t{18}, int_t{9001}) == 1115 );
    REQUIRE( modpow<2>(int_t{300}, int_t{9001}) == 2838 );
    REQUIRE( modpow<2>(int_t{5000}, int_t{9001}) == 4111 );

    REQUIRE( modpow<3>(int_t{18}, int_t{35}) == 29 );
    REQUIRE( modpow<3>(int_t{300}, int_t{35}) == 1 );
    REQUIRE( modpow<3>(int_t{5000}, int_t{35}) == 16 );
    REQUIRE( modpow<3>(int_t{18}, int_t{45}) == 9 );
    REQUIRE( modpow<3>(int_t{300}, int_t{45}) == 36 );
    REQUIRE( modpow<3>(int_t{5000}, int_t{45}) == 36 );
    REQUIRE( modpow<3>(int_t{18}, int_t{450}) == 189 );
    REQUIRE( modpow<3>(int_t{300}, int_t{450}) == 351 );
    REQUIRE( modpow<3>(int_t{5000}, int_t{450}) == 351 );
    REQUIRE( modpow<3>(int_t{18}, int_t{9001}) == 8448 );
    REQUIRE( modpow<3>(int_t{300}, int_t{9001}) == 2038 );
    REQUIRE( modpow<3>(int_t{5000}, int_t{9001}) == 3798 );

}

TEST_CASE( "multiplicative_order", "[multiplicative_order]" ) {

    REQUIRE( multiplicative_order<2>(113) == 28 );
    REQUIRE( multiplicative_order<3>(113) == 112 );

    REQUIRE( multiplicative_order<2>(683) == 22 );
    REQUIRE( multiplicative_order<3>(683) == 31 );
    REQUIRE( mppp::gcd(int_t{22}, int_t{31}) == 1 );
}
