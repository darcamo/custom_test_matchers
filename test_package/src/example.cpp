#include <armadillo>
#include <catch2/catch_all.hpp>
#include "custom_test_matchers/all.h"

using namespace Catch;
using namespace Catch::Matchers;

constexpr const double PI =
    3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;

TEST_CASE("Tests using the catch library") {
    REQUIRE_THAT(2.5 * PI, EqualsAngle(2.5 * PI));
    REQUIRE_THAT(-1.5 * PI, EqualsAngle(-1.5 * PI));
    REQUIRE_THAT(-1.5 * PI, EqualsAngle(0.5 * PI));

    arma::ivec v1{1, 2, 3, 4, 5};
    arma::ivec v2{1, 2, 3, 4, 5};

    REQUIRE_THAT(v1, Equals(v2));
}
