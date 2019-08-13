#ifndef CUSTOM_CATCH_MATCHERS_MATCHERS_IMP_H
#define CUSTOM_CATCH_MATCHERS_MATCHERS_IMP_H

#include "almost_equal_funcs.h"
#include "custom_string_makers.h"
#include "util.h"
#include <armadillo>
#include <catch2/catch.hpp>
#include <spdlog/fmt/fmt.h>

namespace details {

/**
 * A catch2 test matcher for comparing if two armadillo objects are equal.
 *
 * The builder function `Equals` was overloaded with an Armadillo type and is
 * the suggested way to create the match.
 */
template <class ArmaType>
class ArmadilloEqualsMatcher
    : public Catch::Matchers::Impl::MatcherBase<ArmaType> {
protected:
  ArmaType value;
  const double tol;

public:
  explicit ArmadilloEqualsMatcher(ArmaType value, double tol = 1e-10)
      : value(std::move(value)), tol(tol) {}

  // Performs the test for this matcher
  bool match(const ArmaType &v) const override {
    return arma::approx_equal(this->value, v, "absdiff", tol);
  }

  // Produces a string describing what this matcher does. It should
  // include any provided data (in the constructor) and
  // be written as if it were stating a fact (in the output it will be
  // preceded by the value under test).
  [[nodiscard]] std::string describe() const override {
    std::ostringstream ss;
    ss << "is equal to\n" << Catch::StringMaker<ArmaType>::convert(this->value);
    return ss.str();
  }
};
/**
 * A catch2 test matcher for comparing if two tuples (of two elements) are
 * equal.
 */
template <typename T, typename U>
class Tuple2EqualsMatcher
    : public Catch::Matchers::Impl::MatcherBase<std::tuple<T, U>> {
protected:
  using Tuple2 = std::tuple<T, U>;
  Tuple2 t;

public:
  explicit Tuple2EqualsMatcher(Tuple2 t) : t(std::move(t)) {}

  // Performs the test for this matcher
  bool match(const Tuple2 &t) const override;

  // Produces a string describing what this matcher does. It should
  // include any provided data (in the constructor) and
  // be written as if it were stating a fact (in the output it will be
  // preceded by the value under test).
  [[nodiscard]] std::string describe() const override {
    return "is equal to " + Catch::StringMaker<Tuple2>::convert(this->t);
  }
};
/**
 * A catch2 test matcher for comparing if two angles (in radians) are equal.
 *
 * This matcher will ignore full rotations such that two angles can be equal if
 * they "stop" at the same point no matter if the number of full rotations are
 * different.
 */
class AngleEqualsMatcher : public Catch::MatcherBase<double> {
protected:
  // We will cache the value passed to the last call to "match" such that we can
  // show it in the describe function
  mutable double lastMatchedAngle = 0;
  double angle;

public:
  explicit AngleEqualsMatcher(double angle) : angle(angle) {}
  // Performs the test for this matcher
  bool match(const double &t) const override {
    lastMatchedAngle = t;
    auto margin = 1e-4;
    return almostEqualAngles(this->angle, t, margin);
  }

  // Produces a string describing what this matcher does. It should
  // include any provided data (in the constructor) and
  // be written as if it were stating a fact (in the output it will be
  // preceded by the value under test).
  [[nodiscard]] std::string describe() const override {
    auto rad2deg = [](auto angle_rad) {
      constexpr const double PI =
          3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;
      return 180.0 * angle_rad / PI;
    };

    return fmt::format(" (approx {lastMatchedAngleApprox}°) is equal to "
                       "{angle} (approx {angleApprox}°)",
                       fmt::v5::arg("lastMatchedAngleApprox",
                                    rad2deg(fixAngle(lastMatchedAngle))),
                       fmt::arg("angle", angle),
                       fmt::v5::arg("angleApprox", rad2deg(fixAngle(angle))));
  }
};

/**
 * A catch2 test matcher for checking if a value is inside an interval (closed
 * on minimum and open on maximum).
 */
template <typename T>
class IsInRangeMatcher : public Catch::Matchers::Impl::MatcherBase<T> {
protected:
  T minimum;
  T maximum;

public:
  explicit IsInRangeMatcher(T minimum, T maximum)
      : minimum(std::move(minimum)), maximum(std::move(maximum)) {}
  bool match(const T &value) const override {
    return value >= minimum && value < maximum;
  }
  [[nodiscard]] std::string describe() const override {
    std::ostringstream ss;
    ss << "is between " << minimum << " and " << maximum;
    return ss.str();
  }
}; // xxxxx Specializations for some tuples
   // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// Declares a specialization of the match method for a tuple of two doubles.
// This IS IMPORTANT to prevent an implicity instantiation of the templated
// version for the case of a tuple of two doubles. The actual implementation of
// this specialization is provided in the cpp file.
template <>
bool Tuple2EqualsMatcher<double, double>::match(const Tuple2 &t) const {
  return (std::get<0>(this->t) == Approx(std::get<0>(t))) &&
         (std::get<1>(this->t) == Approx(std::get<1>(t)));
}

template <typename T, typename U>
bool Tuple2EqualsMatcher<T, U>::match(const Tuple2 &t) const {
  return this->t == t;
}

} // namespace details

#endif // CUSTOM_CATCH_MATCHERS_MATCHERS_IMP_H
