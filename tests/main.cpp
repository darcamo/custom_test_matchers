#define CATCH_CONFIG_MAIN
#include "all.h"
#include <armadillo>
#include <catch2/catch.hpp>
#include <random>
#include <sstream>
#include <tuple>

using namespace details;
using namespace Catch;

constexpr const double PI =
    3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;

constexpr bool equal(double a, double b, double margin = 1e-10) {
  return std::abs((a - b)) < margin;
}

TEST_CASE("Test util functions") {
  auto seed = std::random_device()();
  std::mt19937 rng(seed);

  SECTION("Test fixAngle") {
    std::uniform_real_distribution<double> dist(0, 2 * PI);

    // Sanity check: fixAngle should not change an angle already in the [0,2PI)
    // range
    for (int i = 0; i < 100; ++i) {
      auto angle = dist(rng);
      REQUIRE(equal(angle, fixAngle(angle)));
    }

    // Check some cases that fall outside the [0, 2PI) range
    REQUIRE(equal(fixAngle(0.99 * 2 * PI), 0.99 * 2 * PI));
    REQUIRE(equal(fixAngle(-0.99 * 2 * PI), 0.01 * 2 * PI));
    REQUIRE(equal(fixAngle(-3 * PI), PI));
    REQUIRE(equal(fixAngle(-PI / 4.0), 7.0 / 4.0 * PI));
    REQUIRE(equal(fixAngle(14.8 * PI), 0.8 * PI));
    REQUIRE(equal(fixAngle(390 * PI / 180.0), 30 * PI / 180));

    for (int j = 0; j < 100; ++j) {
      auto angle = dist(rng);
      REQUIRE(equal(fixAngle(angle + 4 * PI), angle));
      REQUIRE(equal(fixAngle(angle - 8 * PI), angle));
      REQUIRE(equal(fixAngle(-angle), 2 * PI - angle));
    }
  }

  SECTION("Test fixAngleDeg") {
      std::uniform_real_distribution<double> dist(0, 360);

      // Sanity check: fixAngleDeg should not change an angle already in the [0,360.0)
      // range
      for (int i = 0; i < 100; ++i) {
          auto angle = dist(rng);
          REQUIRE(equal(angle, fixAngleDeg(angle)));
      }

      // Check some cases that fall outside the [0, 360.0) range
      REQUIRE(equal(fixAngleDeg(0.99 * 360.0), 0.99 * 360.0));
      REQUIRE(equal(fixAngleDeg(-0.99 * 360.0), 0.01 * 360.0));
      REQUIRE(equal(fixAngleDeg(-3 * 180.0), 180.0));
      REQUIRE(equal(fixAngleDeg(-180.0 / 4.0), 7.0 / 4.0 * 180.0));
      REQUIRE(equal(fixAngleDeg(14.8 * 180.0), 0.8 * 180.0));
      REQUIRE(equal(fixAngleDeg(390 * 180.0 / 180.0), 30 * 180.0 / 180));

      for (int j = 0; j < 100; ++j) {
          auto angle = dist(rng);
          REQUIRE(equal(fixAngleDeg(angle + 4 * 180.0), angle));
          REQUIRE(equal(fixAngleDeg(angle - 8 * 180.0), angle));
          REQUIRE(equal(fixAngleDeg(-angle), 360.0 - angle));
      }
  }

  SECTION("Test Equals for armadillo types") {
    arma::vec v1{1.5, 2.7, -5.5};
    arma::vec v2{1.5, 2.7, -5.5};

    REQUIRE_THAT(v1, Equals(v2));

    arma::vec v2_noisy = v2 + 1e-10;
    REQUIRE_THAT(v1, !Equals(v2_noisy));
    REQUIRE_THAT(v1, Equals(v2_noisy, 1e-8));
    REQUIRE_THAT(v1, EqualsWithinTolerance(v2_noisy, 1e-8));
  }

  SECTION("Test Equals for tuples with two elements") {
    auto t1 = std::make_tuple(1, 5);
    auto t1_other = std::make_tuple(1, 5);
    REQUIRE_THAT(t1, Equals(t1_other));

    auto t2 = std::make_tuple(1.5, -2.6);
    auto t2_other = std::make_tuple(1.5, -2.6 + 1e-14);
    REQUIRE_THAT(t2, Equals(t2_other));
  }

  SECTION("Test InRange") {
    REQUIRE_THAT(1.5, InRange(0, 5));
    REQUIRE_THAT(10.5, !InRange(0, 5));

    REQUIRE_THAT(0, InRange(0, 5));
    REQUIRE_THAT(5, !InRange(0, 5));
    REQUIRE_THAT(5.0 - 1e-12, InRange(0.0, 5.0));
  }

  SECTION("Test EqualsAngle") {
    REQUIRE_THAT(2.5 * PI, EqualsAngle(0.5 * PI));

    REQUIRE_THAT(-1e-16, EqualsAngle(1e-16));
  }

  SECTION("Test EqualsAngleDeg") {
      REQUIRE_THAT(2.5 * 180.0, EqualsAngleDeg(0.5 * 180.0));

      REQUIRE_THAT(-1e-16, EqualsAngleDeg(1e-16));
  }

  SECTION("Test StringMaker") {
    auto convert = [](auto container) {
      return StringMaker<decltype(container)>::convert(container);
    };

    SECTION("Test StringMaker for a vector") {

      SECTION("Small size") {
        {
          arma::ivec v{1, 2, 3};
          std::string expetedStr_v =
              "Vector (x3)\n        1        2        3\n";
          REQUIRE_THAT(convert(v), Equals(expetedStr_v));
        }

        {
          arma::vec v{1, 2, 3};
          std::string expetedStr_v =
              "Vector (x3)\n   1.0000   2.0000   3.0000\n";
          REQUIRE_THAT(convert(v), Equals(expetedStr_v));
        }

        {
          arma::irowvec v{1, 2, 3};
          std::string expetedStr_v =
              "Row Vector (x3)\n        1        2        3\n";
          REQUIRE_THAT(convert(v), Equals(expetedStr_v));
        }

        {
          arma::rowvec v{1, 2, 3};
          std::string expetedStr_v =
              "Row Vector (x3)\n   1.0000   2.0000   3.0000\n";
          REQUIRE_THAT(convert(v), Equals(expetedStr_v));
        }
      }

      SECTION("Larger Size") {
        {
          arma::ivec v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
          std::string expetedStr_v =
              "Vector (x10) -> Only showing from index 0 to 6\n        1       "
              " 2        3        4        5        6        7\n";
          REQUIRE_THAT(convert(v), Equals(expetedStr_v));
        }

        {
          arma::vec v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
          std::string expetedStr_v =
              "Vector (x10) -> Only showing from index 0 to 6\n   1.0000   "
              "2.0000   3.0000   4.0000   5.0000   6.0000   7.0000\n";
          REQUIRE_THAT(convert(v), Equals(expetedStr_v));
        }

        {
          arma::irowvec v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
          std::string expetedStr_v =
              "Row Vector (x10) -> Only showing from index 0 to 6\n        1   "
              "     2        3        4        5        6        7\n";
          REQUIRE_THAT(convert(v), Equals(expetedStr_v));
        }

        {
          arma::rowvec v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
          std::string expetedStr_v =
              "Row Vector (x10) -> Only showing from index 0 to 6\n   1.0000   "
              "2.0000   3.0000   4.0000   5.0000   6.0000   7.0000\n";
          REQUIRE_THAT(convert(v), Equals(expetedStr_v));
        }
      }
    }

    SECTION("Test StringMaker for a matrix") {
      SECTION("Small Size") {

        {
          arma::imat m{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
          std::string expetedStr_m =
              "(3x3)\n        1        2        3\n        4        5        "
              "6\n        7        8        9\n";
          REQUIRE_THAT(convert(m), Equals(expetedStr_m));
        }

        {
          arma::mat m{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
          std::string expetedStr_m =
              "(3x3)\n   1.0000   2.0000   3.0000\n   4.0000   5.0000   "
              "6.0000\n   7.0000   8.0000   9.0000\n";
          REQUIRE_THAT(convert(m), Equals(expetedStr_m));
        }
      }

      SECTION("Larger Size") {
        {
          arma::imat m{{1, 2, 3, 4, 5, 6, 7, 8, 9},
                       {9, 8, 7, 6, 5, 4, 3, 2, 1}};
          std::string expetedStr_m =
              "(2x9) -> Only showing from column 0 to 4\n        1        2    "
              "    3        4        5\n        9        8        7        6   "
              "     5\n";
          REQUIRE_THAT(convert(m), Equals(expetedStr_m));
        }

        {
          arma::mat m{{1, 2, 3, 4, 5, 6, 7, 8, 9}, {9, 8, 7, 6, 5, 4, 3, 2, 1}};
          std::string expetedStr_m =
              "(2x9) -> Only showing from column 0 to 4\n   1.0000   2.0000   "
              "3.0000   4.0000   5.0000\n   9.0000   8.0000   7.0000   6.0000  "
              " 5.0000\n";
          REQUIRE_THAT(convert(m), Equals(expetedStr_m));
        }

        {
          arma::imat m{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {9, 8, 7},
                       {6, 5, 4}, {3, 2, 1}, {1, 2, 3}, {4, 5, 6}};
          std::string expetedStr_m =
              "(8x3) -> Only showing from row 0 to 5\n        1        2       "
              " 3\n        4        5        6\n        7        8        9\n  "
              "      9        8        7\n        6        5        4\n        "
              "3        2        1\n";
          REQUIRE_THAT(convert(m), Equals(expetedStr_m));
        }

        {
          arma::mat m{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {9, 8, 7},
                      {6, 5, 4}, {3, 2, 1}, {1, 2, 3}, {4, 5, 6}};
          std::string expetedStr_m =
              "(8x3) -> Only showing from row 0 to 5\n   1.0000   2.0000   "
              "3.0000\n   4.0000   5.0000   6.0000\n   7.0000   8.0000   "
              "9.0000\n   9.0000   8.0000   7.0000\n   6.0000   5.0000   "
              "4.0000\n   3.0000   2.0000   1.0000\n";
          REQUIRE_THAT(convert(m), Equals(expetedStr_m));
        }
        /// @todo Implement-me
      }
    }
  }
}
